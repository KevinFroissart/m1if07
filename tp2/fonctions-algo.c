#include "fonctions-algo.h"

int sommet_degre_minimum(bool *presence, int *degre_courant, int taille) {
    int degre_mini = 9999;
    int indice_min = -1;
    int i;
    for(i = 0; i < taille; i++) {
        if((degre_courant[i] < degre_mini) && presence[i] == true) {
            indice_min = i;
            degre_mini = degre_courant[i];
        }
    }

    return indice_min;
}

void calcule_stable_max(bool *presence, 
                        int *degre_courant, 
                        nodl *sommets_stable_courant, 
                        graph *G, 
                        int x, 
                        int *noeuds_stable_max, 
                        int *noeuds_stable_courant, 
                        int *noeuds_graphe_courant,
                        nodl *sommets_stable_max,
                        bool mode)
{
    int i;

    // 1. Placer x dans le stable courant
    inserer_en_queue(x, sommets_stable_courant);
    (*noeuds_stable_courant) += 1;
    (*noeuds_graphe_courant) -= 1;

    // 2. Retenir la liste L des voisins courants de x
    nodl* L = G->links[x];

    // 3. Mettre la présence de x et de ses voisins à faux
    presence[x] = false;
    cell *iter = L->prem;
    while(iter != NULL) {
        presence[iter->node] = false;
        (*noeuds_graphe_courant) -= 1;
        iter = iter->suiv;
    }

    // 4. Actualiser le degre courant des sommets restants
    for(i = 0; i < G->n; i++) {
        degre_courant[i] = 0;
        iter = G->links[i]->prem;
        while(iter != NULL) {
            if(presence[iter->node] && presence[i]) {
                degre_courant[i]++;
            }
            iter = iter->suiv;
        }
    }

    // 5. Selectionner un sommet y de degre courant minimum dans le nouveau graphe courant
    int y = sommet_degre_minimum(presence, degre_courant, G->n);

    // Q5. Condition d'arret
    if ((y == -1) && (*noeuds_stable_courant > *noeuds_stable_max)) {
        *noeuds_stable_max = *noeuds_stable_courant;
        vider(sommets_stable_max);
        copy_append(sommets_stable_max, sommets_stable_courant);
    } 
    else if(*noeuds_stable_max < (*noeuds_stable_courant + *noeuds_graphe_courant)) {

        // 6. Faire des appels recursifs à calcule_stable_max
        calcule_stable_max(presence, degre_courant, sommets_stable_courant, G, y, noeuds_stable_max, noeuds_stable_courant, noeuds_graphe_courant, sommets_stable_max, mode);
    
        cell *iter = G->links[y]->prem;
        while(iter != NULL) {
            if(presence[iter->node]) {
                calcule_stable_max(presence, degre_courant, sommets_stable_courant, G, iter->node, noeuds_stable_max, noeuds_stable_courant, noeuds_graphe_courant, sommets_stable_max, mode);
            }
            iter = iter->suiv;
        }

    } 

    // Q10. Liste des stables max
    if(mode && (*noeuds_stable_courant = *noeuds_stable_max)) {
        fprintf(stdout, "Stable max rencontré: ");
        cell* iter = sommets_stable_courant->prem;
        while(iter != NULL) {
            fprintf(stdout,"%d ", iter->node);
            iter = iter->suiv;
        }
        fprintf(stdout, "\n");
    }

    // 7. Defaire l'etape 4
    iter = L->prem;
    while (iter != NULL) { 
        if(presence[iter->node]) degre_courant[iter->node]++;
        iter = iter->suiv;
    }

    // 8. Defaire l'etape 3
    presence[x] = true;        
    (*noeuds_graphe_courant) += 1;

    iter = L->prem;
    while(iter != NULL) {
        presence[iter->node] = true;
        (*noeuds_graphe_courant) += 1;
        iter = iter->suiv;
    }
    
    (*noeuds_stable_courant) -= 1;
    supprimer(sommets_stable_courant->dern, sommets_stable_courant);
}