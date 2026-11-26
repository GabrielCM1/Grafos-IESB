#include <stdio.h>
#include "hamiltoniano.h"

void grafo_iniciar(Grafo *g, int n) {
    g->n = n;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            g->adj[u][v] = 0;
        }
    }
}

void grafo_adicionar_aresta(Grafo *g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

/* caminho[0..pos-1] ja esta montado; tenta colocar um vertice nao usado na posicao pos */
static int backtrack(Grafo *g, int *caminho, int *usado, int pos, int fechar_ciclo) {
    if (pos == g->n) {
        /* No ciclo, o ultimo vertice ainda precisa ser vizinho do primeiro */
        return !fechar_ciclo || g->adj[caminho[pos - 1]][caminho[0]];
    }

    for (int v = 0; v < g->n; v++) {
        if (!usado[v] && g->adj[caminho[pos - 1]][v]) {
            usado[v] = 1;
            caminho[pos] = v;
            if (backtrack(g, caminho, usado, pos + 1, fechar_ciclo)) {
                return 1;
            }
            usado[v] = 0; /* desfaz a escolha e tenta o proximo vizinho */
        }
    }

    return 0;
}

static int buscar(Grafo *g, int *seq, int origem, int fechar_ciclo) {
    int usado[MAX_VERTICES] = {0};
    usado[origem] = 1;
    seq[0] = origem;
    return backtrack(g, seq, usado, 1, fechar_ciclo);
}

int encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho) {
    for (int origem = 0; origem < g->n; origem++) {
        if (buscar(g, caminho, origem, 0)) {
            return 1;
        }
    }
    return 0;
}

int encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo) {
    /* Um ciclo passa por todos os vertices, entao basta comecar pelo 0 */
    return buscar(g, ciclo, 0, 1);
}

void imprimir_sequencia(int *seq, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%s%i", i ? " -> " : "", seq[i]);
    }
    printf("\n");
}
