


#include <stdlib.h>
#include "nodelist.h"
#include "utility.h"

///////////////////////////////////////////////////////////
/////////////////   NODE LISTS   /////////////////////
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// INSERER UNE CELLULE APRES UNE AUTRE DANS UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: une nouvelle cellule contenant la valeur u est inseree dans la liste pointee par l apres la cellule pointee par p 
void inserer_apres (int u, nodl* l, cell* p) {
	
	cell* q;
	if( (q=(cell *)malloc(sizeof(cell))) == NULL )
    report_error("graph_from_file: malloc() error 1");
	q->node=u;
  
	if (p->suiv==NULL) l->dern=q;
	else p->suiv->prec=q;  
    
	q->suiv=p->suiv;
	q->prec=p;
	p->suiv=q;
	
}

//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN TETE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en tete de la liste pointee par l 
void inserer_en_tete (int u, nodl* l) {

	cell* q;
	if( (q=(cell *)malloc(sizeof(cell))) == NULL )
    report_error("graph_from_file: malloc() error 1");
	q->node=u;
  
	if (l->dern==NULL) l->dern=q;
  
	q->suiv=l->prem;
	if (l->prem!=NULL) l->prem->prec=q;
	q->prec=NULL;
	l->prem=q;

}


//////////////////////////////////////////////////////
// INSERER UNE CELLULE EN QUEUE D'UNE LISTE
// precondition: l est non null et *l est initialise
// postcondition: une nouvelle cellule contenant la valeur u est inseree en queue de la liste pointee par l 
void inserer_en_queue (int u, nodl* l) {
	
	if (l->dern!=NULL) inserer_apres (u, l, l->dern);
	else inserer_en_tete (u, l);
}


//////////////////////////////////////////////////////
// SUPPRIMER UNE CELLULE D'UNE LISTE
// precondition: l est non null et pointe sur une liste non vide, p (non null) pointe sur une cellule de la liste pointee par l
// postcondition: la cellule pointee par p est retiree de la liste pointee par l et detruite 
void supprimer (cell* p, nodl* l){

	if (p->prec==NULL) {
		l->prem=p->suiv;
	}
	else {
		p->prec->suiv=p->suiv;
	}
	if (p->suiv==NULL) {
		l->dern=p->prec;
	}
	else {
		p->suiv->prec=p->prec;
	}

	free(p);

}



//////////////////////////////////////////////////////
// LIBERER UNE NODELIST ET TOUTES SES CELLULES
// precondition: aucune
// postcondition: la liste pointee par l est detruite
void free_nodl(nodl* l) {
	if (l!=NULL){
		while (l->prem!=NULL) {
			supprimer(l->prem,l);
		}
		free(l);
	}	
}




