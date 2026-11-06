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

int cobertura_minima_bt(Aresta *a, int n, int m, int *cobertura) {
    /* TODO: implementar backtracking com poda por limite */
    (void)a;
    (void)n;
    (void)m;
    (void)cobertura;
    return -1;
}

int cobertura_gulosa(Aresta *a, int n, int m, int *cobertura) {
    /* TODO: implementar heuristica gulosa (maior grau restante) */
    (void)a;
    (void)n;
    (void)m;
    (void)cobertura;
    return -1;
}
