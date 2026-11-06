#include <stdio.h>
#include "cobertura.h"

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

    /* TODO: experimento para n = 5, 8, 10, 12, 15:
       medir o tempo de cobertura_minima_bt e comparar com cobertura_gulosa */

    return 0;
}
