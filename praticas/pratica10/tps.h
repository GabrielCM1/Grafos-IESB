#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

/* Grafo completo com custo[u][v] = custo de ir de u para v (simetrico) */
typedef struct {
    int n;
    int custo[MAX_VERTICES][MAX_VERTICES];
} InstanciaTSP;

/* Custo da rota rota[0] -> ... -> rota[n-1] -> rota[0] */
int custo_rota(InstanciaTSP *t, int *rota);

/* Fixa a origem 0 e testa as (n-1)! permutacoes dos demais. Preenche rota e retorna o custo otimo. */
int tsp_forca_bruta(InstanciaTSP *t, int *rota);

/* Heuristica construtiva: sempre vai para a cidade nao visitada mais proxima. */
int tsp_vizinho_mais_proximo(InstanciaTSP *t, int origem, int *rota);

/* Heuristica de insercao do mais proximo: escolhe a cidade mais proxima da rota
   e a insere na posicao que menos aumenta o custo. */
int tsp_insercao(InstanciaTSP *t, int *rota);

/* Reducao: aresta existente vira custo 1 e inexistente custo 2.
   G tem ciclo hamiltoniano <=> o TSP otimo custa exatamente n. */
void grafo_para_tsp(Grafo *g, InstanciaTSP *t);

#endif
