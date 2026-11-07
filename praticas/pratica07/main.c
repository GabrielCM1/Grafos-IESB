#include <stdio.h>

#include "bellman_ford.h"

static void executar(GrafoListaPonderado *g, int origem) {
    int dist[10], pred[10];
    if (bellman_ford(g, origem, dist, pred)) {
        for (int v = 0; v < g->num_vertices; v++) {
            printf("%d -> %d: custo %d (pred %d)\n", origem, v, dist[v], pred[v]);
        }
    } else {
        printf("Ciclo negativo: ");
        reconstruir_ciclo_negativo(g, dist, pred);
    }
}

int main(void) {
    // Grafo com pesos negativos, sem ciclo negativo
    GrafoListaPonderado *g = grafo_criar(5);
    grafo_adicionar_aresta(g, 0, 1, 6);
    grafo_adicionar_aresta(g, 0, 3, 7);
    grafo_adicionar_aresta(g, 1, 2, 5);
    grafo_adicionar_aresta(g, 1, 3, 8);
    grafo_adicionar_aresta(g, 1, 4, -4);
    grafo_adicionar_aresta(g, 2, 1, -2);
    grafo_adicionar_aresta(g, 3, 2, -3);
    grafo_adicionar_aresta(g, 3, 4, 9);
    grafo_adicionar_aresta(g, 4, 0, 2);
    grafo_adicionar_aresta(g, 4, 2, 7);
    printf("Grafo 1:\n");
    executar(g, 0);
    grafo_destruir(g);

    // Ciclo 1 -> 2 -> 3 -> 1 com custo 1 - 3 + 1 = -1
    g = grafo_criar(5);
    grafo_adicionar_aresta(g, 0, 1, 4);
    grafo_adicionar_aresta(g, 1, 2, 1);
    grafo_adicionar_aresta(g, 2, 3, -3);
    grafo_adicionar_aresta(g, 3, 1, 1);
    grafo_adicionar_aresta(g, 3, 4, 2);
    printf("\nGrafo 2:\n");
    executar(g, 0);
    grafo_destruir(g);

    return 0;
}
