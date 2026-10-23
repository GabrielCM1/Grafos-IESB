#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H
    

typedef struct No
{
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;


typedef struct {
    int u, v;
} Aresta;


GrafoLista *criar_grafo(int n);
void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);
void imprimir_grafo(GrafoLista *g);

int contar_arestas(GrafoLista *g);
int grau(GrafoLista *g, int v);
int existe_aresta(GrafoLista *g, int u, int v);

void dfs_articulacoes(GrafoLista *g, int u, int *descoberta, int *low, int *pai,
                      int *eh_articulacao, int *tempo);


int *encontrar_articulacoes(GrafoLista *g, int *quantidade);


Aresta *detectar_pontes(GrafoLista *g, int *quantidade);

#endif