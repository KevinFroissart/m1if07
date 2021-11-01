

#ifndef _NODELIST_

#define _NODELIST_

//#include <stdio.h>


///////////////////////////////////////////////////////////
///////////////////   NODE LISTS   ////////////////////////
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// CELLULE D'UNE LISTE DE NOEUDS
typedef struct cell{
  int node;
  struct cell* suiv;
  struct cell* prec;
} cell;

//////////////////////////////////////////////////////
// LISTE DE NOEUDS
typedef struct nodl{
  cell* prem;
  cell* dern;
} nodl;


//////////////////////////////////////////////////////
// INITIALISER UNE LISTE A LISTE VIDE
// precondition: l est non null et pointe effectivement sur une nodl deja allouee
// postcondition: la nodl pointee par l est initiallisee a liste vide
void init_vide(nodl* l);


//////////////////////////////////////////////////////
// VIDER UNE LISTE
// precondition: aucune
// postcondition: supprime toutes les cellules de la liste pointee par l en liberant l'espace qu'elles prennent, la liste pointee par l est laissee vide
void vider(nodl* l);


//////////////////////////////////////////////////////
// VIDER ET LIBERER UNE LISTE
// precondition: aucune
// postcondition: libere l'espace memoire pris par la liste pointee par l et toutes ses cellules 
void free_nodl(nodl* l);


//////////////////////////////////////////////////////
// INSERER UNE CELLULE APRES UNE AUTRE DANS UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: une nouvelle cellule contenant la valeur u est inseree dans la liste pointee par l apres la cellule pointee par p 
void inserer_apres (int u, nodl* l, cell* p);


//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN TETE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en tete de la liste pointee par l 
void inserer_en_tete (int u, nodl* l);


//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN QUEUE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en queue de la liste pointee par l 
void inserer_en_queue (int u, nodl* l);


//////////////////////////////////////////////////////
// SUPPRIMER UNE CELLULE D'UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: la cellule pointee par p est retiree de la liste pointee par l et detruite 
void supprimer (cell* p, nodl* l);


//////////////////////////////////////////////////////
// COPIER LE CONTENU D'UNE LISTE A LA FIN D'UNE AUTRE
// precondition: l_dest et l_sour sont non null et *l_dest et *l_sour sont initialisees
// postcondition: les cellules de l_sour sont copiees et ajoutees a la fin de l_dest, dans le meme ordre
void copy_append (nodl* l_dest, nodl* l_sour);


//////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif



