#include <stdio.h>

#include "agm.h"

int main(void) {
    Aresta arestas[] = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7},
        {2, 5, 4}, {2, 8, 2}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10},
        {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7},
    };
    int n = 9, m = sizeof(arestas) / sizeof(Aresta);

    GrafoListaPonderado *g = grafo_criar(n);
    for (int i = 0; i < m; i++) {
        grafo_adicionar_aresta(g, arestas[i].u, arestas[i].v, arestas[i].peso);
    }

    Aresta agm[8];
    int total = kruskal(arestas, m, n, agm);
    printf("Kruskal:\n");
    for (int i = 0; i < n - 1; i++) printf("  %d - %d (%d)\n", agm[i].u, agm[i].v, agm[i].peso);
    printf("  custo total: %d\n", total);

    int pred[9];
    total = prim(g, pred);
    printf("Prim:\n");
    for (int v = 1; v < n; v++) printf("  %d - %d\n", pred[v], v);
    printf("  custo total: %d\n", total);

    grafo_destruir(g);
    return 0;
}
