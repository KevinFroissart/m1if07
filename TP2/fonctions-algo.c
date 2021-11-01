#include "fonctions-algo.h"


int indice_degret_courant_minimun(bool* presence, int* degre_courant, int taille) {
    int degre_mini = 9999;
    int indice_min = -1;
    for (int i = 0; i < taille; i++) {
        if(degre_courant[i] < degre_mini && presence[i] == true) {
            indice_min = i;
        }
    }
    return indice_min;
}

void calcul_stable_max(bool** presence, int** degre_courant, nodl** sommets_stable_courant, int x, graph* G, int* noeuds_stables_max, int* noeuds_stables_courant, int* noeuds_restants) {    
    inserer_en_queue(x, *sommets_stable_courant); // Placer x dans le stable courant 1

    *noeuds_stables_courant += 1;
    *noeuds_restants -= 1;
    fprintf(stderr,"n restant %d.\n", *noeuds_restants);


    nodl* L = G->links[x]; // Retenir la liste L des voisins courant de x 2

    (*presence)[x] = false;

    cell* iter = L->prem;
    while (iter != NULL) { // Mettre la presence de x et de ses voisins à faux 3
        (*presence)[iter->node] = false;
        *noeuds_restants -= 1;
        iter = iter->suiv;
    }

    for(int i = 0; i < G->n; i++) { // Actualiser le degre courant des sommets restants 4
        iter = G->links[i]->prem;
        (*degre_courant)[i] = 0;
        fprintf(stderr,"%d.\n", i);
        while (iter != NULL) { 
            fprintf(stderr,"node est %d.\n", iter->node);
            if ((*presence)[iter->node] && (*presence)[i]) {
                (*degre_courant)[i]++;
            }
            iter = iter->suiv;
        }
    }

    for(int i = 0; i < G->n; i++) {
        if((*presence)[i]) fprintf(stderr,"%d est TRUE, degré est %d.\n", i, (*degre_courant)[i]);
        if(!(*presence)[i]) fprintf(stderr,"%d est FALSE, degré est %d.\n", i, (*degre_courant)[i]);
    }
    
    int y = indice_degret_courant_minimun(*presence, *degre_courant, *noeuds_restants); //Selectionner un sommet y de degret minimum 5

    fprintf(stderr,"%d < %d + %d.\n", *noeuds_stables_max, *noeuds_stables_courant, *noeuds_restants);
    if ((*noeuds_stables_max < (*noeuds_stables_courant + *noeuds_restants)) == true) {
                fprintf(stderr,"true.\n");

    }
    if ((*noeuds_stables_max < (*noeuds_stables_courant + *noeuds_restants)) == true) { // Faire les appels recursifs a calculeçstable_max pour chaque sommet z parmi y et ses voisins 6
        fprintf(stderr,"Boucle Recursion.\n");
        calcul_stable_max(presence, degre_courant, sommets_stable_courant, y, G, noeuds_stables_max, noeuds_stables_courant, noeuds_restants);
        fprintf(stderr,"Après Boucle Recursion.\n");
        // iter = G->links[y]->prem;
        // while (iter != NULL) {
        //             fprintf(stderr,"Boucle Recursion while.\n");
        //     if ((*presence)[iter->node] == true) calcul_stable_max(presence, degre_courant, sommets_stable_courant, iter->node, G, noeuds_stables_max, noeuds_stables_courant, noeuds_restants);
        //     iter = iter->suiv;
        // }
    }

    if (*noeuds_stables_courant > *noeuds_stables_max) {
        *noeuds_stables_max = *noeuds_stables_courant;
    }

    fprintf(stderr,"n restant %d.\n", *noeuds_restants);
    for(int i = 0; i < *noeuds_restants; i++) { // Défaire l'étape 4
        fprintf(stderr,"i %d.\n", i);
        iter = G->links[i]->prem;
        (*degre_courant)[iter->node] = 0;
        while (iter != NULL) { 
            (*degre_courant)[iter->node]++;
            iter = iter->suiv;
        }
    }
    fprintf(stderr,"Après for 1.\n");


    // Défaire l'étape 3
    (*presence)[x] = true;
    *noeuds_restants += 1;
    iter = L->prem;
    while(iter != NULL) { 
        (*presence)[iter->node] = true;
        *noeuds_restants += 1;
        iter = iter->suiv;
    }
    fprintf(stderr,"Après for 2.\n");
    //supprimer((*sommets_stable_courant)->dern, *sommets_stable_courant);
    *noeuds_stables_courant -= 1;
    fprintf(stderr,"fonction terminée.\n");
} 