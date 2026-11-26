#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#define MAX_VERTICES 20

/* Grafo nao-direcionado em matriz de adjacencia (adj[u][v] = 1 se existe a aresta) */
typedef struct {
    int n;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

void grafo_iniciar(Grafo *g, int n);
void grafo_adicionar_aresta(Grafo *g, int u, int v);

/* Backtracking: tenta estender o caminho vertice a vertice, testando cada origem.
   Preenche caminho[0..n-1] e retorna 1 se existir caminho hamiltoniano; 0 caso contrario. */
int encontrar_caminho_hamiltoniano_bt(Grafo *g, int *caminho);

/* Igual ao caminho, mas fixa a origem 0 e exige aresta do ultimo vertice de volta ao 0. */
int encontrar_ciclo_hamiltoniano_bt(Grafo *g, int *ciclo);

void imprimir_sequencia(int *seq, int tam);

#endif
