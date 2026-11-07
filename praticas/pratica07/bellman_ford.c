#include "bellman_ford.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

GrafoListaPonderado *grafo_criar(int num_vertices) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->adj = calloc(num_vertices, sizeof(NoAdjPonderado *));
    return g;
}

void grafo_adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso) {
    NoAdjPonderado *novo = malloc(sizeof(NoAdjPonderado));
    novo->vertice = destino;
    novo->peso = peso;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

void grafo_destruir(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        while (g->adj[i] != NULL) {
            NoAdjPonderado *prox = g->adj[i]->prox;
            free(g->adj[i]);
            g->adj[i] = prox;
        }
    }
    free(g->adj);
    free(g);
}

// Uma passada de relaxação em todas as arestas; retorna o último vértice relaxado ou -1
static int relaxar_arestas(GrafoListaPonderado *g, int *dist, int *pred) {
    int ultimo = -1;
    for (int u = 0; u < g->num_vertices; u++) {
        if (dist[u] == INT_MAX) continue; // evita overflow em INT_MAX + peso
        for (NoAdjPonderado *a = g->adj[u]; a != NULL; a = a->prox) {
            if (dist[u] + a->peso < dist[a->vertice]) {
                dist[a->vertice] = dist[u] + a->peso;
                pred[a->vertice] = u;
                ultimo = a->vertice;
            }
        }
    }
    return ultimo;
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    for (int v = 0; v < g->num_vertices; v++) {
        dist[v] = (v == origem) ? 0 : INT_MAX;
        pred[v] = -1;
    }

    // n-1 iterações bastam: um caminho mínimo simples tem no máximo n-1 arestas
    for (int i = 1; i < g->num_vertices; i++) {
        if (relaxar_arestas(g, dist, pred) == -1) return 1; // convergiu antes
    }

    // Se a n-ésima iteração ainda relaxa alguma aresta, existe ciclo negativo
    return relaxar_arestas(g, dist, pred) == -1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred) {
    int x = relaxar_arestas(g, dist, pred);
    if (x == -1) {
        printf("sem ciclo negativo\n");
        return;
    }

    // Retroceder n vezes garante que x caia dentro do ciclo
    for (int i = 0; i < g->num_vertices; i++) x = pred[x];

    // pred[] percorre o ciclo de trás pra frente; guarda e imprime na ordem certa
    int *ciclo = malloc(g->num_vertices * sizeof(int)), tam = 0;
    int v = x;
    do {
        ciclo[tam++] = v;
        v = pred[v];
    } while (v != x);

    printf("%d", x);
    for (int i = tam - 1; i >= 0; i--) printf(" -> %d", ciclo[i]);
    printf("\n");
    free(ciclo);
}
