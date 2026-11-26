#include <limits.h>
#include "tps.h"

int custo_rota(InstanciaTSP *t, int *rota) {
    int total = 0;
    for (int i = 0; i < t->n; i++) {
        total += t->custo[rota[i]][rota[(i + 1) % t->n]];
    }
    return total;
}

static void trocar(int *a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/* Gera as permutacoes de atual[pos..n-1] por trocas; custo ja soma as arestas de atual[0..pos-1] */
static void permutar(InstanciaTSP *t, int *atual, int pos, int custo, int *melhor, int *melhor_custo) {
    if (pos == t->n) {
        int total = custo + t->custo[atual[t->n - 1]][atual[0]]; /* volta para a origem */
        if (total < *melhor_custo) {
            *melhor_custo = total;
            for (int i = 0; i < t->n; i++) {
                melhor[i] = atual[i];
            }
        }
        return;
    }

    for (int i = pos; i < t->n; i++) {
        trocar(atual, pos, i);
        permutar(t, atual, pos + 1, custo + t->custo[atual[pos - 1]][atual[pos]], melhor, melhor_custo);
        trocar(atual, pos, i); /* desfaz a troca */
    }
}

int tsp_forca_bruta(InstanciaTSP *t, int *rota) {
    int atual[MAX_VERTICES];
    for (int i = 0; i < t->n; i++) {
        atual[i] = i;
        rota[i] = i;
    }
    if (t->n <= 1) {
        return 0;
    }

    int melhor_custo = INT_MAX;
    permutar(t, atual, 1, 0, rota, &melhor_custo); /* posicao 0 fica fixa na origem */
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(InstanciaTSP *t, int origem, int *rota) {
    int visitado[MAX_VERTICES] = {0};
    rota[0] = origem;
    visitado[origem] = 1;

    for (int i = 1; i < t->n; i++) {
        int atual = rota[i - 1], prox = -1;
        for (int v = 0; v < t->n; v++) {
            if (!visitado[v] && (prox == -1 || t->custo[atual][v] < t->custo[atual][prox])) {
                prox = v;
            }
        }
        rota[i] = prox;
        visitado[prox] = 1;
    }

    return custo_rota(t, rota);
}

int tsp_insercao(InstanciaTSP *t, int *rota) {
    int na_rota[MAX_VERTICES] = {0};
    int tam = 1;
    rota[0] = 0;
    na_rota[0] = 1;

    while (tam < t->n) {
        /* 1) Seleciona a cidade fora da rota mais proxima de alguma cidade da rota */
        int k = -1, dist_k = INT_MAX;
        for (int v = 0; v < t->n; v++) {
            if (na_rota[v]) {
                continue;
            }
            for (int i = 0; i < tam; i++) {
                if (t->custo[rota[i]][v] < dist_k) {
                    dist_k = t->custo[rota[i]][v];
                    k = v;
                }
            }
        }

        /* 2) Insere k entre rota[i] e rota[i+1] onde o acrescimo de custo e menor */
        int pos = 0, menor_acrescimo = INT_MAX;
        for (int i = 0; i < tam; i++) {
            int a = rota[i], b = rota[(i + 1) % tam];
            int acrescimo = t->custo[a][k] + t->custo[k][b] - t->custo[a][b];
            if (acrescimo < menor_acrescimo) {
                menor_acrescimo = acrescimo;
                pos = i + 1;
            }
        }

        for (int i = tam; i > pos; i--) {
            rota[i] = rota[i - 1];
        }
        rota[pos] = k;
        na_rota[k] = 1;
        tam++;
    }

    return custo_rota(t, rota);
}

void grafo_para_tsp(Grafo *g, InstanciaTSP *t) {
    t->n = g->n;
    for (int u = 0; u < g->n; u++) {
        for (int v = 0; v < g->n; v++) {
            t->custo[u][v] = (u == v) ? 0 : (g->adj[u][v] ? 1 : 2);
        }
    }
}
