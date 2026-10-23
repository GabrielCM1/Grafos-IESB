#include "dijkstra.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

GrafoListaPonderado *grafo_criar(int num_vertices) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;

    g->adj = malloc(num_vertices * sizeof(NoAdjPonderado *));
    for (int i = 0; i < g->num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void grafo_adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso) {
    (void)g;
    (void)origem;
    (void)destino;
    (void)peso;
    // TODO
}

void grafo_destruir(GrafoListaPonderado *g) {
    (void)g;
    // TODO
}

MinHeap *criar_min_heap(int capacidade) {
    (void)capacidade;
    // TODO
    return NULL;
}

void inserir_heap(MinHeap *h, int vertice, int distancia) {
    (void)h;
    (void)vertice;
    (void)distancia;
    // TODO
}

NoHeap extrair_minimo(MinHeap *h) {
    (void)h;
    NoHeap vazio = {-1, INT_MAX};
    // TODO
    return vazio;
}

void diminuir_chave(MinHeap *h, int vertice, int nova_distancia) {
    (void)h;
    (void)vertice;
    (void)nova_distancia;
    // TODO
}

int heap_vazio(MinHeap *h) {
    return h == NULL || h->tamanho == 0;
}

void destruir_min_heap(MinHeap *h) {
    (void)h;
    // TODO
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    (void)g;
    (void)origem;
    (void)dist;
    (void)pred;
    // TODO
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    (void)origem;
    (void)destino;
    (void)pred;
    // TODO
}
