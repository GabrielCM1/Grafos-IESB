#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

static void analisar(GrafoLista *g, const char *titulo) {
    int *dist = malloc(g->n * sizeof(int));
    int *pred = malloc(g->n * sizeof(int));
    int *entrada = malloc(g->n * sizeof(int));
    int *saida = malloc(g->n * sizeof(int));
    int *visitado = calloc(g->n, sizeof(int));
    int tempo = 0;

    printf("==== %s ====\n", titulo);

    bfs(g, 0, dist, pred);
    printf("BFS a partir de 0 (vertice: distancia, predecessor)\n");
    for (int i = 0; i < g->n; i++) {
        printf("  %d: %d, %d\n", i, dist[i], pred[i]);
    }

    // roda a DFS em todo vertice ainda nao visitado para cobrir o grafo inteiro
    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) dfs_recursiva(g, i, visitado, entrada, saida, &tempo);
    }
    printf("DFS recursiva (vertice: entrada, saida)\n");
    for (int i = 0; i < g->n; i++) {
        printf("  %d: %d, %d\n", i, entrada[i], saida[i]);
    }

    for (int i = 0; i < g->n; i++) visitado[i] = 0;
    printf("DFS iterativa a partir de 0: ");
    dfs_iterativa(g, 0, visitado);
    printf("\n");

    printf("Componentes conexos: %d\n", contar_componentes(g));
    printf("Tem ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("Eh bipartido? %s\n\n", eh_bipartido(g) ? "Sim" : "Nao");

    free(dist);
    free(pred);
    free(entrada);
    free(saida);
    free(visitado);
}

int main(void) {
    // triangulo 0-1-2 (ciclo impar), aresta solta 3-4 e o vertice 5 isolado
    GrafoLista *g1 = criar_grafo_lista(6);
    inserir_aresta_lista(g1, 0, 1);
    inserir_aresta_lista(g1, 1, 2);
    inserir_aresta_lista(g1, 2, 0);
    inserir_aresta_lista(g1, 3, 4);
    analisar(g1, "Grafo 1: 3 componentes, com ciclo impar");
    liberar_grafo_lista(g1);

    // caminho 0-1-2-3-4: conexo, sem ciclo e bipartido
    GrafoLista *g2 = criar_grafo_lista(5);
    for (int i = 0; i < 4; i++) {
        inserir_aresta_lista(g2, i, i + 1);
    }
    analisar(g2, "Grafo 2: caminho simples");
    liberar_grafo_lista(g2);

    return 0;
}
