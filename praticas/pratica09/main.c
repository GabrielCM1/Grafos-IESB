#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

#define REPETICOES 1000

int main(void) {
    int cobertura[MAX_VERTICES];
    Aresta arestas[MAX_ARESTAS];

    /* Exemplo da aula 06: V = {A, B, C, D}, E = {{A, B}, {B, C}, {C, D}} */
    arestas[0].u = 0; arestas[0].v = 1;
    arestas[1].u = 1; arestas[1].v = 2;
    arestas[2].u = 2; arestas[2].v = 3;

    /* C1 = {A, B, D} */
    cobertura[0] = 1;
    cobertura[1] = 1;
    cobertura[2] = 0;
    cobertura[3] = 1;
    printf("C1 = {A, B, D} eh cobertura? %i\n", eh_cobertura(arestas, cobertura, 3));

    /* C2 = {B, C} */
    cobertura[0] = 0;
    cobertura[1] = 1;
    cobertura[2] = 1;
    cobertura[3] = 0;
    printf("C2 = {B, C} eh cobertura? %i\n", eh_cobertura(arestas, cobertura, 3));

    /* C3 = {C} */
    cobertura[0] = 0;
    cobertura[1] = 0;
    cobertura[2] = 1;
    cobertura[3] = 0;
    printf("C3 = {C} eh cobertura? %i\n", eh_cobertura(arestas, cobertura, 3));

    printf("Minima (backtracking): %i vertice(s)\n", cobertura_minima_bt(arestas, 4, 3, cobertura));
    printf("Gulosa (maior grau): %i vertice(s)\n", cobertura_gulosa(arestas, 4, 3, cobertura));

    /* Experimento: grafos aleatorios (probabilidade 1/2 por aresta), semente fixa */
    int tamanhos[] = {5, 8, 10, 12, 15};
    srand(42);
    printf("\n  n   m | otimo  tempo(ms) | guloso  tempo(ms)\n");
    for (int k = 0; k < 5; k++) {
        int n = tamanhos[k], m = 0;
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                if (rand() % 2) {
                    arestas[m].u = u;
                    arestas[m].v = v;
                    m++;
                }
            }
        }

        /* Repete cada medicao pois uma execucao isolada fica abaixo da resolucao do clock() */
        int otimo = 0, guloso = 0;
        clock_t t = clock();
        for (int r = 0; r < REPETICOES; r++) {
            otimo = cobertura_minima_bt(arestas, n, m, cobertura);
        }
        double tempo_bt = 1000.0 * (clock() - t) / CLOCKS_PER_SEC / REPETICOES;

        t = clock();
        for (int r = 0; r < REPETICOES; r++) {
            guloso = cobertura_gulosa(arestas, n, m, cobertura);
        }
        double tempo_guloso = 1000.0 * (clock() - t) / CLOCKS_PER_SEC / REPETICOES;

        printf("%3i %3i | %5i %10.3f | %6i %10.3f\n", n, m, otimo, tempo_bt, guloso, tempo_guloso);
    }

    return 0;
}
