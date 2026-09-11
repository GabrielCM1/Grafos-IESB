#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafo_lista.h"

// Fila (FIFO) usada pela BFS: array circular de tamanho fixo
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int contar_componentes(GrafoLista *g);
int eh_bipartido(GrafoLista *g);

#endif
