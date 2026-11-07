#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

typedef struct NoAdjPonderado {
    int vertice;
    int peso;
    struct NoAdjPonderado *prox;
} NoAdjPonderado;

typedef struct {
    int num_vertices;
    NoAdjPonderado **adj;
} GrafoListaPonderado;

DSU *dsu_criar(int n);
void dsu_destruir(DSU *d);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);

GrafoListaPonderado *grafo_criar(int num_vertices);
void grafo_adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso); // não orientada
void grafo_destruir(GrafoListaPonderado *g);

// Preenche agm[] com as n-1 arestas escolhidas e retorna o custo total (ordena arestas[])
int kruskal(Aresta *arestas, int m, int n, Aresta *agm);

// Preenche pred[] (árvore enraizada em 0) e retorna o custo total
int prim(GrafoListaPonderado *g, int *pred);

#endif
