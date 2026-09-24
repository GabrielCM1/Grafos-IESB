#include <stdlib.h>
#include "busca_largura.h"

// ---- fila circular: cada vertice entra no maximo uma vez, entao n posicoes bastam ----
static Fila *criar_fila(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    f->dados = malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = f->fim = f->tamanho = 0;
    return f;
}

static void enfileirar(Fila *f, int v) {
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade; // volta pro inicio do array quando chega no fim
    f->tamanho++;
}

static int desenfileirar(Fila *f) {
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

static void liberar_fila(Fila *f) {
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->n; i++) {
        dist[i] = -1; // -1 marca "ainda nao visitado"
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->n);
    dist[origem] = 0;
    enfileirar(f, origem);

    while (f->tamanho > 0) {
        int u = desenfileirar(f);
        for (No *a = g->adj[u]; a != NULL; a = a->prox) {
            if (dist[a->destino] == -1) {
                dist[a->destino] = dist[u] + 1; // um passo a mais que u
                pred[a->destino] = u;
                enfileirar(f, a->destino);
            }
        }
    }
    liberar_fila(f);
}

int contar_componentes(GrafoLista *g) {
    int *visitado = calloc(g->n, sizeof(int));
    Fila *f = criar_fila(g->n);
    int componentes = 0;

    // uma BFS por vertice ainda nao alcancado: cada uma varre um componente inteiro
    for (int i = 0; i < g->n; i++) {
        if (visitado[i]) continue;
        componentes++;
        visitado[i] = 1;
        enfileirar(f, i);

        while (f->tamanho > 0) {
            int u = desenfileirar(f);
            for (No *a = g->adj[u]; a != NULL; a = a->prox) {
                if (!visitado[a->destino]) {
                    visitado[a->destino] = 1;
                    enfileirar(f, a->destino);
                }
            }
        }
    }
    liberar_fila(f);
    free(visitado);
    return componentes;
}

int eh_bipartido(GrafoLista *g) {
    int *cor = malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) {
        cor[i] = -1; // sem cor = nao visitado
    }

    Fila *f = criar_fila(g->n);
    int bipartido = 1;

    // 2-coloracao: vizinho sempre recebe a cor oposta; cores iguais = nao bipartido
    for (int i = 0; i < g->n && bipartido; i++) {
        if (cor[i] != -1) continue;
        cor[i] = 0;
        enfileirar(f, i);

        while (f->tamanho > 0 && bipartido) {
            int u = desenfileirar(f);
            for (No *a = g->adj[u]; a != NULL; a = a->prox) {
                if (cor[a->destino] == -1) {
                    cor[a->destino] = 1 - cor[u];
                    enfileirar(f, a->destino);
                } else if (cor[a->destino] == cor[u]) {
                    bipartido = 0; // dois vizinhos com a mesma cor: ciclo impar
                    break;
                }
            }
        }
    }
    liberar_fila(f);
    free(cor);
    return bipartido;
}
