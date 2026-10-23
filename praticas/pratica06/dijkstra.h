#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct NoAdjPonderado {
    int vertice;
    int peso;
    struct NoAdjPonderado *prox;
} NoAdjPonderado;

typedef struct {
    int num_vertices;
    NoAdjPonderado **adj;
} GrafoListaPonderado;

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

GrafoListaPonderado *grafo_criar(int num_vertices);
void grafo_adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void grafo_destruir(GrafoListaPonderado *g);

MinHeap *criar_min_heap(int capacidade);
void inserir_heap(MinHeap *h, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int nova_distancia);
int heap_vazio(MinHeap *h);
void destruir_min_heap(MinHeap *h);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);

void reconstruir_caminho(int origem, int destino, int *pred);

#endif
