#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

typedef struct {
    int n;      // número de vértices do grafo
    int **adj;  // matriz de adjacência (n x n)
} GrafoMatriz;

GrafoMatriz *criar_grafo_matriz(int n);
void inserir_aresta_matriz(GrafoMatriz *g, int u, int v);
void remover_aresta_matriz(GrafoMatriz *g, int u, int v);
int grau_matriz(GrafoMatriz *g, int v);
int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v);
void liberar_grafo_matriz(GrafoMatriz *g);

#endif