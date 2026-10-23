#include <stdlib.h>
#include "dag.h"

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau_entrada = calloc(g->n, sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));
    int inicio = 0, fim = 0;

    // conta quantos arcos chegam em cada vertice
    for (int u = 0; u < g->n; u++) {
        for (No *a = g->adj[u]; a != NULL; a = a->prox) {
            grau_entrada[a->destino]++;
        }
    }

    // 'ordem' e a fila e o resultado ao mesmo tempo: a ordem de saida da fila
    // ja e a ordem topologica, entao nao precisa de um segundo array
    for (int v = 0; v < g->n; v++) {
        if (grau_entrada[v] == 0) ordem[fim++] = v;
    }

    while (inicio < fim) {
        int u = ordem[inicio++];
        for (No *a = g->adj[u]; a != NULL; a = a->prox) {
            // ao remover u, cada sucessor perde um pre-requisito
            if (--grau_entrada[a->destino] == 0) ordem[fim++] = a->destino;
        }
    }
    free(grau_entrada);

    if (fim < g->n) { // sobrou vertice preso num ciclo: nao e DAG
        free(ordem);
        *tamanho = 0;
        return NULL;
    }
    *tamanho = g->n;
    return ordem;
}

static void visitar(GrafoLista *g, int u, int *visitado, int *ordem, int *pos) {
    visitado[u] = 1;
    for (No *a = g->adj[u]; a != NULL; a = a->prox) {
        if (!visitado[a->destino]) visitar(g, a->destino, visitado, ordem, pos);
    }
    ordem[--(*pos)] = u; // empilha na saida: preenche o array de tras pra frente
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (!eh_dag(g)) { // a DFS so ordena se nao houver ciclo
        *tamanho = 0;
        return NULL;
    }

    int *visitado = calloc(g->n, sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));
    int pos = g->n;

    for (int v = 0; v < g->n; v++) {
        if (!visitado[v]) visitar(g, v, visitado, ordem, &pos);
    }
    free(visitado);
    *tamanho = g->n;
    return ordem;
}

// 0 = nao visitado, 1 = na pilha de recursao, 2 = finalizado
static int ha_ciclo(GrafoLista *g, int u, int *estado) {
    estado[u] = 1;
    for (No *a = g->adj[u]; a != NULL; a = a->prox) {
        if (estado[a->destino] == 1) return 1; // arco de volta: fecha um ciclo
        if (estado[a->destino] == 0 && ha_ciclo(g, a->destino, estado)) return 1;
    }
    estado[u] = 2;
    return 0;
}

int eh_dag(GrafoLista *g) {
    int *estado = calloc(g->n, sizeof(int));
    int ciclo = 0;

    for (int v = 0; v < g->n && !ciclo; v++) {
        if (estado[v] == 0) ciclo = ha_ciclo(g, v, estado);
    }
    free(estado);
    return !ciclo;
}
