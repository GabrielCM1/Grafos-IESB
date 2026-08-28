#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n) {
    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g->adj[i] = calloc(n, sizeof(int)); // calloc já zera (sem arestas)
    }
    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1; // não-direcionado: vale nos dois sentidos
}

void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int grau_matriz(GrafoMatriz *g, int v) {
    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[v][i] == 1) {
            grau++;
        }
    }
    return grau;
}