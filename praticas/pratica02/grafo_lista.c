#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;

    g->adj = malloc(n * sizeof(No *));
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL; // cada lista começa vazia
    }
    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    // cria o nó novo para v e coloca na lista de u
    No *novo_u = malloc(sizeof(No));
    novo_u->destino = v;
    novo_u->prox = g->adj[u]; // o novo nó aponta pro antigo primeiro
    g->adj[u] = novo_u;       // e vira o novo primeiro da lista

    // faz o mesmo do outro lado (grafo não-direcionado)
    No *novo_v = malloc(sizeof(No));
    novo_v->destino = u;
    novo_v->prox = g->adj[v];
    g->adj[v] = novo_v;
}

static void remover_de_uma_lista(No **cabeca, int alvo) {
    No *atual = *cabeca;
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->destino == alvo) {
            if (anterior == NULL) {
                *cabeca = atual->prox; // removendo o primeiro da lista
            } else {
                anterior->prox = atual->prox; // "pula" o nó removido
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    remover_de_uma_lista(&g->adj[u], v);
    remover_de_uma_lista(&g->adj[v], u);
}

int grau_lista(GrafoLista *g, int v) {
    int grau = 0;
    No *atual = g->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    No *atual = g->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}