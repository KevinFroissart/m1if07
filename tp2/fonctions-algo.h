#ifndef _FONCTIONS_ALGO_
#define _FONCTIONS_ALGO_

#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "nodelist.h"

int sommet_degre_minimum(bool *presence, int *degre_courant, int taille);
void calcule_stable_max(bool *presence,
                        int *degre_courant, 
                        nodl *sommets_stable_courant, 
                        graph *G, int x, 
                        int *noeuds_stable_max, 
                        int *noeuds_stable_courant, 
                        int *noeuds_graphe_courant,
                        nodl *sommets_stable_max,
                        bool mode);

#endif