#ifndef DAG_H
#define DAG_H

#include "grafo_lista.h"

// as duas ordenacoes devolvem um array de g->n vertices (o chamador da free)
// ou NULL quando o digrafo tem ciclo; *tamanho recebe 0 nesse caso
int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif
