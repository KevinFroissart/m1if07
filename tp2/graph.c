

//#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "graph.h"

#define MAX_LINE_LENGTH 1000


///////////////////////////////////////////////////////////
////////////   GRAPH MANAGEMENT FUNCTIONS   ///////////////
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// CHARGER UN GRAPHE A PARTIR D'UN FLUX
// precondition: f est initialise et contient un graphe au format suivant: la premiere ligne contient un entier n qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe representee par deux entiers compris entre 0 et n-1 (les identifiants des sommets) separes par un espace
// postcondition: initialise une structure graph, l'affecte du graphe lu sur le flux f et retourne un pointeur sur la structure graph ainsi construite
graph* graph_from_file(FILE *f){
  char line[MAX_LINE_LENGTH];
  int i, u, v;
  graph *g;

  if( (g=(graph *)malloc(sizeof(graph))) == NULL )
    report_error("graph_from_file: malloc() error 1");
  
  /* read n */
  if( fgets(line,MAX_LINE_LENGTH,f) == NULL )
    report_error("graph_from_file: read error (fgets) 1");
  if( sscanf(line, "%d\n", &(g->n)) != 1 )
    report_error("graph_from_file: read error (sscanf) 2");
  
  /* create space for links and degrees*/
  if (g->n==0){
    g->links = NULL; g->degrees = NULL;
  }
  else {
  
  	if( (g->degrees=(int*)malloc(g->n*sizeof(int))) == NULL )
      report_error("graph_from_file: malloc() error 3");
    for(i=0;i<g->n;i++){
    	g->degrees[i]=0;
    }
      
    if( (g->links=(nodl**)malloc(g->n*sizeof(nodl*))) == NULL )
      report_error("graph_from_file: malloc() error 3");
    for(i=0;i<g->n;i++){
    	if( (g->links[i]=(nodl*)malloc(sizeof(nodl))) == NULL )
      	report_error("graph_from_file: malloc() error 3");
	    g->links[i]->prem=NULL;
	    g->links[i]->dern=NULL;
    }
    
  }

  /* read the links */
  while (fgets(line,MAX_LINE_LENGTH,f) != NULL ){
    if( sscanf(line, "%d %d\n", &u, &v) != 2 ){
      fprintf(stderr,"Attempt to scan link #%d failed. Line read:%s\n", i, line);
      report_error("graph_from_file; read error (sscanf) 3");
    }
    if ( (u>=g->n) || (v>=g->n) || (u<0) || (v<0) ) {
      fprintf(stderr,"Line just read: %s",line);
      report_error("graph_from_file: bad node number");
    }
    
    inserer_en_queue(v, g->links[u]);
    inserer_en_queue(u, g->links[v]);
    g->degrees[u]++;
    g->degrees[v]++;
  }
  
  /* compute the number of links */
  g->m=0;
  for(i=0;i<g->n;i++)
    g->m += g->degrees[i];
  g->m /= 2;
  
  return g;
}


//////////////////////////////////////////////////////
// ECRIRE UN GRAPHE DANS UN FLUX
// precondition: f et g sont initialises
// postcondition: le graphe pointe par g est ecrit sur le flux f dans le format suivant: la premiere ligne contient un entier qui est le nombre de sommets du graphe, chaque ligne suivante contient une arete du graphe representee par deux entiers (les identifiants des sommets) separes par un espace
void write_graph(FILE *f, graph* g){

	int u;
	cell* p;

	fprintf(f,"%d\n",g->n);
	for (u=0;u<g->n;u++) {
		p=g->links[u]->prem;
  	while (p!=NULL) {
			if (p->node<u) fprintf(f,"%d %d\n",u,p->node);
			p=p->suiv;
		}
	}
	fflush(f);	
}



//////////////////////////////////////////////////////
// LIBERER UN GRAPHE
// precondition: aucune
// postcondition: le graphe pointe par g est detruit
void free_graph(graph *g){
	int i;
  if (g!=NULL) {
    if (g->links!=NULL) {
    	for(i=0;i<g->n;i++) {
    		free_nodl(g->links[i]);
    	}
      free(g->links);
    }
    if (g->degrees!=NULL)
      free(g->degrees);
    free(g);
  }
}


