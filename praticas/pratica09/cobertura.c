#include "cobertura.h"

int eh_cobertura(Aresta *a, int *cobertura, int m) {
    for (int i = 0; i < m; i++) {
        int u = a[i].u;
        int v = a[i].v;
        if (!cobertura[u] && !cobertura[v]) {
            return 0;
        }
    }

    return 1;
}

/* Decide para cada vertice i se entra (1) ou nao (0) na cobertura atual */
static void backtrack(Aresta *a, int n, int m, int i, int tam, int *atual, int *melhor, int *melhor_tam) {
    /* Poda por limite: com tam vertices ja nao da para superar a melhor solucao */
    if (tam >= *melhor_tam) {
        return;
    }

    if (i == n) {
        if (eh_cobertura(a, atual, m)) {
            *melhor_tam = tam;
            for (int v = 0; v < n; v++) {
                melhor[v] = atual[v];
            }
        }
        return;
    }

    atual[i] = 1;
    backtrack(a, n, m, i + 1, tam + 1, atual, melhor, melhor_tam);
    atual[i] = 0;
    backtrack(a, n, m, i + 1, tam, atual, melhor, melhor_tam);
}

int cobertura_minima_bt(Aresta *a, int n, int m, int *cobertura) {
    int atual[MAX_VERTICES];
    int melhor_tam = n;

    /* Todos os vertices sempre formam uma cobertura: serve de limite inicial */
    for (int v = 0; v < n; v++) {
        cobertura[v] = 1;
    }

    backtrack(a, n, m, 0, 0, atual, cobertura, &melhor_tam);
    return melhor_tam;
}

int cobertura_gulosa(Aresta *a, int n, int m, int *cobertura) {
    int tam = 0;
    for (int v = 0; v < n; v++) {
        cobertura[v] = 0;
    }

    for (;;) {
        /* Grau de cada vertice contando so as arestas ainda descobertas */
        int grau[MAX_VERTICES] = {0};
        for (int i = 0; i < m; i++) {
            if (!cobertura[a[i].u] && !cobertura[a[i].v]) {
                grau[a[i].u]++;
                grau[a[i].v]++;
            }
        }

        int maior = 0;
        for (int v = 1; v < n; v++) {
            if (grau[v] > grau[maior]) {
                maior = v;
            }
        }

        if (grau[maior] == 0) {
            return tam; /* nenhuma aresta descoberta restante */
        }
        cobertura[maior] = 1;
        tam++;
    }
}
