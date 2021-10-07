

#ifndef _GRAPH_

#define _GRAPH_



#include <stdio.h>
#include "nodelist.h"


///////////////////////////////////////////////////////////
////////////   GRAPH MANAGEMENT FUNCTIONS   ///////////////
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// LA STRUCTURE STOCKANT UN GRAPHE A n SOMMETS ET m ARETES
// links la liste des voisins
typedef struct graph{
  int n;
  int m;
  nodl** links;
  int *degrees;
} graph;


//////////////////////////////////////////////////////
// CHARGER UN GRAPHE A PARTIR D'UN FLUX
// precondition: f est initialise et contient un graphe au format suivant: la premiere ligne contient un entier n qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe representee par deux entiers compris entre 0 et n-1 (les identifiants des sommets) separes par un espace
// postcondition: initialise une structure graph, l'affecte du graphe lu sur le flux f et retourne un pointeur sur la structure graph ainsi construite
graph* graph_from_file(FILE *f);

//////////////////////////////////////////////////////
// ECRIRE UN GRAPHE DANS UN FLUX
// precondition: f et g sont initialises
// postcondition: le graphe pointe par g est ecrit sur le flux f dans le format suivant: la premiere ligne contient un entier qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe representee par deux entiers (les identifiants des sommets) separes par un espace
void write_graph(FILE *f, graph* g);



//////////////////////////////////////////////////////
// LIBERER UN GRAPHE
// precondition: aucune
// postcondition: le graphe pointe par g est detruit
void free_graph(graph *g);




#endif




