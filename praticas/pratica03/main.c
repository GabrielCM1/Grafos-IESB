#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void exibir(const char *rotulo, int *ordem, int tamanho) {
    printf("  %-6s: ", rotulo);
    if (ordem == NULL) {
        printf("impossivel, o digrafo tem ciclo\n");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", ordem[i]);
    }
    printf("\n");
}

static void analisar(GrafoLista *g, const char *titulo) {
    int tamanho = 0;

    printf("==== %s ====\n", titulo);
    printf("  Eh DAG? %s\n", eh_dag(g) ? "Sim" : "Nao");

    int *kahn = ordenacao_topologica_kahn(g, &tamanho);
    exibir("Kahn", kahn, tamanho);
    free(kahn);

    int *dfs = ordenacao_topologica_dfs(g, &tamanho);
    exibir("DFS", dfs, tamanho);
    free(dfs);

    printf("\n");
}

int main(void) {
    // pre-requisitos: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
    GrafoLista *dag = criar_grafo_lista(6);
    inserir_arco_lista(dag, 5, 2);
    inserir_arco_lista(dag, 5, 0);
    inserir_arco_lista(dag, 4, 0);
    inserir_arco_lista(dag, 4, 1);
    inserir_arco_lista(dag, 2, 3);
    inserir_arco_lista(dag, 3, 1);
    analisar(dag, "Digrafo aciclico");
    liberar_grafo_lista(dag);

    // 0->1->2->0 fecha um ciclo, entao nao existe ordenacao topologica
    GrafoLista *ciclico = criar_grafo_lista(3);
    inserir_arco_lista(ciclico, 0, 1);
    inserir_arco_lista(ciclico, 1, 2);
    inserir_arco_lista(ciclico, 2, 0);
    analisar(ciclico, "Digrafo com ciclo");
    liberar_grafo_lista(ciclico);

    return 0;
}
