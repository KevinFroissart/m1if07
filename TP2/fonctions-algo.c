#include "fonctions-algo.h"

int indice_degret_courant_minimun(bool* presence, int* degre_courant, int taille) {
    int degre_mini = 9999;
    int indice_min = -1;
    for (int i = 0; i < taille; i++) {
        if((degre_courant[i] < degre_mini) && presence[i] == true) {
            indice_min = i;
            degre_mini = degre_courant[i];
        }
    }

    return indice_min;
}

void calcul_stable_max(bool** presence, int** degre_courant, nodl** sommets_stable_courant, int x, graph* G, int* noeuds_stables_max, int* noeuds_stables_courant, int* noeuds_restants) {    
    inserer_en_queue(x, *sommets_stable_courant); // Placer x dans le stable courant 1

    *noeuds_stables_courant += 1;
    *noeuds_restants -= 1;

    nodl* L = G->links[x]; // Retenir la liste L des voisins courant de x 2

    (*presence)[x] = false;

    cell* iter = L->prem;
    while (iter != NULL) { // Mettre la presence de x et de ses voisins à faux 3
        (*presence)[iter->node] = false;
        *noeuds_restants -= 1;
        iter = iter->suiv;
    }

    for (int i = 0; i < G->n; i++) { // Actualiser le degre courant des sommets restants 4
        iter = G->links[i]->prem;
        (*degre_courant)[i] = 0;
        while (iter != NULL) { 
            if ((*presence)[iter->node] && (*presence)[i]) {
                (*degre_courant)[i]++;
            }
            iter = iter->suiv;
        }
    }
    
    int y = indice_degret_courant_minimun(*presence, *degre_courant, G->n); //Selectionner un sommet y de degret minimum 5


    if (*noeuds_stables_max < (*noeuds_stables_courant + *noeuds_restants)) { // Faire les appels recursifs a calcule_stable_max pour chaque sommet z parmi y et ses voisins 6
        calcul_stable_max(presence, degre_courant, sommets_stable_courant, y, G, noeuds_stables_max, noeuds_stables_courant, noeuds_restants);
    }

    if (*noeuds_stables_courant > *noeuds_stables_max) {
        *noeuds_stables_max = *noeuds_stables_courant;
    }

    for(int i = 0; i < *noeuds_restants; i++) { // Défaire l'étape 4
        iter = G->links[i]->prem;
        (*degre_courant)[iter->node] = 0;
        while (iter != NULL) { 
            (*degre_courant)[iter->node]++;
            iter = iter->suiv;
        }
    }

    // Défaire l'étape 3
    (*presence)[x] = true;
    *noeuds_restants += 1;
    iter = L->prem;
    while(iter != NULL) { 
        (*presence)[iter->node] = true;
        *noeuds_restants += 1;
        iter = iter->suiv;
    }
    *noeuds_stables_courant -= 1;
} 