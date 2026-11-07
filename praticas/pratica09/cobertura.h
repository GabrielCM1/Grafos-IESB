#ifndef COBERTURA_H
#define COBERTURA_H

#define MAX_VERTICES 20
#define MAX_ARESTAS (MAX_VERTICES * (MAX_VERTICES - 1) / 2)

typedef struct {
    int u;
    int v;
} Aresta;

/* Retorna 1 se todas as m arestas tem ao menos uma ponta na cobertura; 0 caso contrario. */
int eh_cobertura(Aresta *a, int *cobertura, int m);

/* Backtracking com poda por limite. Preenche cobertura e retorna o tamanho minimo. */
int cobertura_minima_bt(Aresta *a, int n, int m, int *cobertura);

/* Heuristica gulosa (maior grau restante). Preenche cobertura e retorna seu tamanho. */
int cobertura_gulosa(Aresta *a, int n, int m, int *cobertura);

#endif
