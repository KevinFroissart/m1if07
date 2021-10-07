#include <stdlib.h>
#include "fonctions-algo.h"

void contraction_simulee(int* identifiant_groupe, 
                         nodl* liste_sommets_groupe, 
                         int* nb_sommet_groupe, 
                         int groupe_lead, 
                         int groupe_a_fusionner)
{
    //On fait l'addition des tailles dans le groupe lead et on passe l'autre à 0
    nb_sommet_groupe[groupe_lead] += nb_sommet_groupe[groupe_a_fusionner];
    nb_sommet_groupe[groupe_a_fusionner] = 0;

    //On modifie l'identifiant du groupe à fusionner par celui du lead
    identifiant_groupe[groupe_a_fusionner] = identifiant_groupe[groupe_lead];

    //On étend la liste des sommets du groupe lead avec ceux du groupe à fusionner
    cell* p = liste_sommets_groupe[groupe_a_fusionner].prem;
    while(p != NULL) {
        identifiant_groupe[p->node] = groupe_lead;
        p = p->suiv;
    }
    liste_sommets_groupe[groupe_lead].dern->suiv = liste_sommets_groupe[groupe_a_fusionner].prem;
    liste_sommets_groupe[groupe_a_fusionner].prem->prec = liste_sommets_groupe[groupe_lead].dern;
    liste_sommets_groupe[groupe_lead].dern = liste_sommets_groupe[groupe_a_fusionner].dern;
    liste_sommets_groupe[groupe_a_fusionner].dern = NULL;
    liste_sommets_groupe[groupe_a_fusionner].prem = NULL;

  //  liste_sommets_groupe[groupe_lead].dern = liste_sommets_groupe[groupe_a_fusionner].prem;
   // liste_sommets_groupe[groupe_a_fusionner].prem = liste_sommets_groupe[groupe_lead].dern;
}
