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

MinHeap *criar_min_heap(int capacidade) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->dados = malloc(capacidade * sizeof(NoHeap));
    h->posicao = malloc(capacidade * sizeof(int));
    h->capacidade = capacidade;
    h->tamanho = 0;
    for (int i = 0; i < capacidade; i++) {
        h->posicao[i] = -1; // -1 = vértice fora do heap
    }
    return h;
}

// Troca dois nós do heap mantendo o mapeamento posicao[] atualizado
static void trocar(MinHeap *h, int i, int j) {
    NoHeap tmp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = tmp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

static void subir(MinHeap *h, int i) {
    while (i > 0 && h->dados[i].distancia < h->dados[(i - 1) / 2].distancia) {
        trocar(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

static void descer(MinHeap *h, int i) {
    for (;;) {
        int menor = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia) menor = esq;
        if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia) menor = dir;
        if (menor == i) return;
        trocar(h, i, menor);
        i = menor;
    }
}

void inserir_heap(MinHeap *h, int vertice, int distancia) {
    if (h->tamanho == h->capacidade) return;
    int i = h->tamanho++;
    h->dados[i] = (NoHeap){vertice, distancia};
    h->posicao[vertice] = i;
    subir(h, i);
}

NoHeap extrair_minimo(MinHeap *h) {
    NoHeap vazio = {-1, INT_MAX};
    if (heap_vazio(h)) return vazio;

    NoHeap min = h->dados[0];
    trocar(h, 0, --h->tamanho);
    h->posicao[min.vertice] = -1;
    descer(h, 0);
    return min;
}

// O(log V): posicao[] localiza o vértice no heap sem precisar de busca linear
void diminuir_chave(MinHeap *h, int vertice, int nova_distancia) {
    int i = h->posicao[vertice];
    if (i == -1 || nova_distancia >= h->dados[i].distancia) return;
    h->dados[i].distancia = nova_distancia;
    subir(h, i);
}

int heap_vazio(MinHeap *h) {
    return h == NULL || h->tamanho == 0;
}

void destruir_min_heap(MinHeap *h) {
    free(h->dados);
    free(h->posicao);
    free(h);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    MinHeap *h = criar_min_heap(g->num_vertices);
    for (int v = 0; v < g->num_vertices; v++) {
        dist[v] = (v == origem) ? 0 : INT_MAX;
        pred[v] = -1;
        inserir_heap(h, v, dist[v]);
    }

    while (!heap_vazio(h)) {
        int u = extrair_minimo(h).vertice;
        if (dist[u] == INT_MAX) break; // restantes são inalcançáveis

        for (NoAdjPonderado *a = g->adj[u]; a != NULL; a = a->prox) {
            if (dist[u] + a->peso < dist[a->vertice]) {
                dist[a->vertice] = dist[u] + a->peso;
                pred[a->vertice] = u;
                diminuir_chave(h, a->vertice, dist[a->vertice]);
            }
        }
    }
    destruir_min_heap(h);
}


void reconstruir_caminho(int origem, int destino, int *pred) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("sem caminho");
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}
