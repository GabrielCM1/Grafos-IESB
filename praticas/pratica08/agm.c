#include "agm.h"

#include <limits.h>
#include <stdlib.h>

DSU *dsu_criar(int n) {
    DSU *d = malloc(sizeof(DSU));
    d->pai = malloc(n * sizeof(int));
    d->rank = calloc(n, sizeof(int));
    d->n = n;
    for (int i = 0; i < n; i++) d->pai[i] = i;
    return d;
}

void dsu_destruir(DSU *d) {
    free(d->pai);
    free(d->rank);
    free(d);
}

// Compressão de caminho: todos no caminho passam a apontar direto para a raiz
int find(DSU *d, int x) {
    if (d->pai[x] != x) d->pai[x] = find(d, d->pai[x]);
    return d->pai[x];
}

// União por rank: a árvore mais baixa fica embaixo, mantendo a altura O(log n)
void unir(DSU *d, int x, int y) {
    x = find(d, x);
    y = find(d, y);
    if (x == y) return;
    if (d->rank[x] < d->rank[y]) {
        int tmp = x; x = y; y = tmp;
    }
    d->pai[y] = x;
    if (d->rank[x] == d->rank[y]) d->rank[x]++;
}

GrafoListaPonderado *grafo_criar(int num_vertices) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->adj = calloc(num_vertices, sizeof(NoAdjPonderado *));
    return g;
}

static void inserir_adj(GrafoListaPonderado *g, int u, int v, int peso) {
    NoAdjPonderado *novo = malloc(sizeof(NoAdjPonderado));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void grafo_adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    inserir_adj(g, u, v, peso);
    inserir_adj(g, v, u, peso);
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

static int comparar_peso(const void *a, const void *b) {
    return ((const Aresta *)a)->peso - ((const Aresta *)b)->peso;
}

int kruskal(Aresta *arestas, int m, int n, Aresta *agm) {
    qsort(arestas, m, sizeof(Aresta), comparar_peso); // O(E log E)
    DSU *d = dsu_criar(n);
    int k = 0, total = 0;
    for (int i = 0; i < m && k < n - 1; i++) {
        // Só aceita a aresta se ligar componentes diferentes (senão forma ciclo)
        if (find(d, arestas[i].u) != find(d, arestas[i].v)) {
            unir(d, arestas[i].u, arestas[i].v);
            agm[k++] = arestas[i];
            total += arestas[i].peso;
        }
    }
    dsu_destruir(d);
    return total;
}

// Min-heap de vértices ordenado por chave[]; pos[] permite diminuir a chave em O(log V)
typedef struct {
    int *v, *pos, tam;
    const int *chave;
} MinHeap;

static void trocar(MinHeap *h, int i, int j) {
    int tmp = h->v[i];
    h->v[i] = h->v[j];
    h->v[j] = tmp;
    h->pos[h->v[i]] = i;
    h->pos[h->v[j]] = j;
}

static void subir(MinHeap *h, int i) {
    while (i > 0 && h->chave[h->v[i]] < h->chave[h->v[(i - 1) / 2]]) {
        trocar(h, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

static int extrair_minimo(MinHeap *h) {
    int min = h->v[0];
    trocar(h, 0, --h->tam);
    h->pos[min] = -1; // -1 = já saiu do heap (está na árvore)
    for (int i = 0;;) {
        int menor = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < h->tam && h->chave[h->v[esq]] < h->chave[h->v[menor]]) menor = esq;
        if (dir < h->tam && h->chave[h->v[dir]] < h->chave[h->v[menor]]) menor = dir;
        if (menor == i) break;
        trocar(h, i, menor);
        i = menor;
    }
    return min;
}

int prim(GrafoListaPonderado *g, int *pred) {
    int n = g->num_vertices, total = 0;
    int *chave = malloc(n * sizeof(int));
    MinHeap h = {malloc(n * sizeof(int)), malloc(n * sizeof(int)), n, chave};
    for (int v = 0; v < n; v++) {
        chave[v] = (v == 0) ? 0 : INT_MAX; // 0 na raiz e INF no resto já é um heap válido
        pred[v] = -1;
        h.v[v] = h.pos[v] = v;
    }

    while (h.tam > 0) {
        int u = extrair_minimo(&h);
        if (chave[u] == INT_MAX) break; // restantes estão em outro componente
        total += chave[u];

        // chave[v] = menor aresta que liga v à árvore atual
        for (NoAdjPonderado *a = g->adj[u]; a != NULL; a = a->prox) {
            int v = a->vertice;
            if (h.pos[v] != -1 && a->peso < chave[v]) {
                chave[v] = a->peso;
                pred[v] = u;
                subir(&h, h.pos[v]);
            }
        }
    }
    free(h.v);
    free(h.pos);
    free(chave);
    return total;
}
