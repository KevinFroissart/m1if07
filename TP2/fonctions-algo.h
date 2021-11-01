#ifndef _FONCTIONS_ALGO_
#define _FONCTIONS_ALGO_

#include "nodelist.h"
#include "graph.h"
#include <stdbool.h>
#include <stdlib.h>

int indice_degret_courant_minimun(bool* presence, int* degre_courant, int taille);
void calcul_stable_max(bool** presence, int** degre_courant, nodl** sommets_stable_courant, int x, graph* G, int* noeuds_stables_max, int* noeuds_stables_courant, int* noeuds_restants);

#endif