#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafo_lista.h"

// Pilha (LIFO) usada pela DFS iterativa
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *entrada, int *saida, int *tempo);
void dfs_iterativa(GrafoLista *g, int origem, int *visitado);
int tem_ciclo(GrafoLista *g);

#endif
