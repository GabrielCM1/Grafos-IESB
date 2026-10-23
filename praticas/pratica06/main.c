#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"

int main(void) {
    GrafoListaPonderado *g = grafo_criar(5);

    // TODO: adicionar arestas, rodar dijkstra e imprimir os caminhos

    grafo_destruir(g);
    return 0;
}
