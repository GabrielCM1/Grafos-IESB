#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

int main(void) {
    GrafoListaPonderado *g = grafo_criar(5);

    grafo_adicionar_aresta(g, 0, 1, 10);
    grafo_adicionar_aresta(g, 0, 3, 5);
    grafo_adicionar_aresta(g, 1, 2, 1);
    grafo_adicionar_aresta(g, 1, 3, 2);
    grafo_adicionar_aresta(g, 2, 4, 4);
    grafo_adicionar_aresta(g, 3, 1, 3);
    grafo_adicionar_aresta(g, 3, 2, 9);
    grafo_adicionar_aresta(g, 3, 4, 2);
    grafo_adicionar_aresta(g, 4, 0, 7);
    grafo_adicionar_aresta(g, 4, 2, 6);

    int dist[5], pred[5], origem = 0;
    dijkstra(g, origem, dist, pred);

    for (int v = 0; v < g->num_vertices; v++) {
        printf("%d -> %d (custo %d): ", origem, v, dist[v]);
        reconstruir_caminho(origem, v, pred);
        printf("\n");
    }

    grafo_destruir(g);
    return 0;
}
