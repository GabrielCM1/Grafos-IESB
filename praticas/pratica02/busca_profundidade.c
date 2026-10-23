#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

// ---- pilha: como o vertice ja entra marcado, n posicoes bastam ----
static Pilha *criar_pilha(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    p->dados = malloc(capacidade * sizeof(int));
    p->capacidade = capacidade;
    p->topo = -1; // -1 = pilha vazia
    return p;
}

static void empilhar(Pilha *p, int v) {
    p->dados[++p->topo] = v;
}

static int desempilhar(Pilha *p) {
    return p->dados[p->topo--];
}

static void liberar_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *entrada, int *saida, int *tempo) {
    visitado[u] = 1;
    entrada[u] = (*tempo)++; // tempo de descoberta

    for (No *a = g->adj[u]; a != NULL; a = a->prox) {
        if (!visitado[a->destino]) {
            dfs_recursiva(g, a->destino, visitado, entrada, saida, tempo);
        }
    }
    saida[u] = (*tempo)++; // tempo de finalizacao (ja explorou todos os vizinhos)
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado) {
    Pilha *p = criar_pilha(g->n);
    visitado[origem] = 1;
    empilhar(p, origem);

    while (p->topo >= 0) {
        int u = desempilhar(p);
        printf("%d ", u);
        for (No *a = g->adj[u]; a != NULL; a = a->prox) {
            if (!visitado[a->destino]) {
                visitado[a->destino] = 1; // marca na hora de empilhar, evita repetir
                empilhar(p, a->destino);
            }
        }
    }
    liberar_pilha(p);
}

// num grafo nao-direcionado, achar um vizinho ja visitado que nao seja o pai = ciclo
static int ha_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;
    for (No *a = g->adj[u]; a != NULL; a = a->prox) {
        if (!visitado[a->destino]) {
            if (ha_ciclo(g, a->destino, u, visitado)) return 1;
        } else if (a->destino != pai) {
            return 1;
        }
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = calloc(g->n, sizeof(int));
    int ciclo = 0;

    for (int i = 0; i < g->n && !ciclo; i++) {
        if (!visitado[i]) ciclo = ha_ciclo(g, i, -1, visitado);
    }
    free(visitado);
    return ciclo;
}
