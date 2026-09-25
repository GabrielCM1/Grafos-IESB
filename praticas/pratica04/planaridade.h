#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"


int eh_planar_euler(GrafoLista *g);


int contem_subdivisao_k5(GrafoLista *g);
int contem_subdivisao_k33(GrafoLista *g);


int eh_planar_kuratowski(GrafoLista *g);

int verificar_planaridade(GrafoLista *g);

#endif