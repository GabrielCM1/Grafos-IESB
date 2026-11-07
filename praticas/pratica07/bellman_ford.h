#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

typedef struct NoAdjPonderado {
    int vertice;
    int peso;
    struct NoAdjPonderado *prox;
} NoAdjPonderado;

typedef struct {
    int num_vertices;
    NoAdjPonderado **adj;
} GrafoListaPonderado;

GrafoListaPonderado *grafo_criar(int num_vertices);
void grafo_adicionar_aresta(GrafoListaPonderado *g, int origem, int destino, int peso);
void grafo_destruir(GrafoListaPonderado *g);

// Retorna 1 (sucesso) ou 0 (ciclo negativo alcançável a partir da origem)
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred);

#endif
