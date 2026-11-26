#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

#define REPETICOES_HEURISTICA 1000

static void testar_grafo(const char *nome, Grafo *g) {
    int seq[MAX_VERTICES], rota[MAX_VERTICES];
    InstanciaTSP t;

    printf("%s\n", nome);
    printf("  Caminho hamiltoniano: ");
    if (encontrar_caminho_hamiltoniano_bt(g, seq)) {
        imprimir_sequencia(seq, g->n);
    } else {
        printf("nao existe\n");
    }

    printf("  Ciclo hamiltoniano:   ");
    if (encontrar_ciclo_hamiltoniano_bt(g, seq)) {
        seq[g->n] = seq[0];
        imprimir_sequencia(seq, g->n + 1);
    } else {
        printf("nao existe\n");
    }

    /* Reducao para o TSP: custo otimo == n se e somente se ha ciclo hamiltoniano */
    grafo_para_tsp(g, &t);
    int otimo = tsp_forca_bruta(&t, rota);
    printf("  Reducao para TSP: custo otimo %i (n = %i) -> %s\n\n", otimo, g->n,
           otimo == g->n ? "tem ciclo" : "nao tem ciclo");
}

static void imprimir_rota(const char *metodo, InstanciaTSP *t, int *rota, int custo) {
    printf("  %-22s custo %3i: ", metodo, custo);
    for (int i = 0; i < t->n; i++) {
        printf("%i -> ", rota[i]);
    }
    printf("%i\n", rota[0]);
}

int main(void) {
    Grafo g;

    /* G1: ciclo 0-1-2-3-4-0 com a corda 0-2 */
    grafo_iniciar(&g, 5);
    grafo_adicionar_aresta(&g, 0, 1);
    grafo_adicionar_aresta(&g, 1, 2);
    grafo_adicionar_aresta(&g, 2, 3);
    grafo_adicionar_aresta(&g, 3, 4);
    grafo_adicionar_aresta(&g, 4, 0);
    grafo_adicionar_aresta(&g, 0, 2);
    testar_grafo("G1 (ciclo com corda):", &g);

    /* G2: caminho simples 0-1-2-3-4 (tem caminho, mas nao fecha ciclo) */
    grafo_iniciar(&g, 5);
    grafo_adicionar_aresta(&g, 0, 1);
    grafo_adicionar_aresta(&g, 1, 2);
    grafo_adicionar_aresta(&g, 2, 3);
    grafo_adicionar_aresta(&g, 3, 4);
    testar_grafo("G2 (caminho simples):", &g);

    /* G3: estrela com centro 0 (nem caminho nem ciclo) */
    grafo_iniciar(&g, 5);
    for (int v = 1; v < 5; v++) {
        grafo_adicionar_aresta(&g, 0, v);
    }
    testar_grafo("G3 (estrela):", &g);

    /* TSP com 5 cidades */
    InstanciaTSP t = {5, {
        { 0,  3,  4,  2,  7},
        { 3,  0,  4,  6,  3},
        { 4,  4,  0,  5,  8},
        { 2,  6,  5,  0,  6},
        { 7,  3,  8,  6,  0},
    }};
    int rota[MAX_VERTICES];
    printf("TSP com 5 cidades:\n");
    int c = tsp_forca_bruta(&t, rota);
    imprimir_rota("Forca bruta:", &t, rota, c);
    c = tsp_vizinho_mais_proximo(&t, 0, rota);
    imprimir_rota("Vizinho mais proximo:", &t, rota, c);
    c = tsp_insercao(&t, rota);
    imprimir_rota("Insercao:", &t, rota, c);

    /* Experimento: custos aleatorios entre 1 e 100, semente fixa */
    int tamanhos[] = {5, 8, 10, 12};
    srand(42);
    printf("\n  n | otimo  tempo(ms) | vizinho  tempo(ms) | insercao  tempo(ms)\n");
    for (int k = 0; k < 4; k++) {
        int n = tamanhos[k];
        t.n = n;
        for (int u = 0; u < n; u++) {
            t.custo[u][u] = 0;
            for (int v = u + 1; v < n; v++) {
                t.custo[u][v] = t.custo[v][u] = 1 + rand() % 100;
            }
        }

        /* Execucoes rapidas ficam abaixo da resolucao do clock(), entao repetimos */
        int rep_bt = n <= 8 ? 100 : 1;
        int otimo = 0, vizinho = 0, insercao = 0;
        clock_t inicio = clock();
        for (int r = 0; r < rep_bt; r++) {
            otimo = tsp_forca_bruta(&t, rota);
        }
        double tempo_bt = 1000.0 * (clock() - inicio) / CLOCKS_PER_SEC / rep_bt;

        inicio = clock();
        for (int r = 0; r < REPETICOES_HEURISTICA; r++) {
            vizinho = tsp_vizinho_mais_proximo(&t, 0, rota);
        }
        double tempo_vizinho = 1000.0 * (clock() - inicio) / CLOCKS_PER_SEC / REPETICOES_HEURISTICA;

        inicio = clock();
        for (int r = 0; r < REPETICOES_HEURISTICA; r++) {
            insercao = tsp_insercao(&t, rota);
        }
        double tempo_insercao = 1000.0 * (clock() - inicio) / CLOCKS_PER_SEC / REPETICOES_HEURISTICA;

        printf("%3i | %5i %10.3f | %7i %10.3f | %8i %10.3f\n",
               n, otimo, tempo_bt, vizinho, tempo_vizinho, insercao, tempo_insercao);
    }

    return 0;
}
