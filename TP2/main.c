
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
//#include <unistd.h>

#include "utility.h"
#include "nodelist.h"
#include "graph.h"
#include "fonctions-algo.h"

/******************/
/* Default values */
/******************/




/********************/
/* Output functions */
/********************/

// print help
void usage(char *c){
	fprintf(stderr,"Usage: %s -h\n",c);
	fprintf(stderr,"  -h: print current help.\n");
	fprintf(stderr,"  -l: list all maximum stable sets, with possible repetitions.\n");
	fprintf(stderr,"  -i \"inputname\": input file containing the graph (default value is stdin).\n");
	fprintf(stderr,"  -o \"outputname\": output results in a file named \"outputname\" (default value is stdout).\n");
	exit(-1);
}




/**************************************************************/
/**************************************************************/
/**************************************************************/
/***************************        ***************************/
/***************************  MAIN  ***************************/
/***************************        ***************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/

int main(int argc, char **argv){


///////////////////////////////////////////////////////////
//////////   DECLARATIONS AND DEFAULT VALUES   ////////////
///////////////////////////////////////////////////////////
 
	FILE* fin=NULL;
	FILE* fout=NULL;

	graph * G=NULL;

	int i;



///////////////////////////////////////////////////////////
////////////////   PARSE COMMAND LINE   ///////////////////
///////////////////////////////////////////////////////////


	// default values
	char name_in[100]="";
	char name_out[100]="";
	bool input_file_given=false;
	bool output_file_given=false;
	bool liste=false;

	// user's values
  
	for (i=1; i<argc; i++) {
		if ((strcmp(argv[i],"-h")==0) || (strcmp(argv[i],"--help")==0) ) {
			usage(argv[0]);     
		}
		else if ((strcmp(argv[i],"-l")==0) || (strcmp(argv[i],"--liste")==0) ) {
			liste=true;
		}
		else if ((strcmp(argv[i],"-i")==0) || (strcmp(argv[i],"--input")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			input_file_given=true;
			strcpy(name_in,argv[++i]);
		}
		else if ((strcmp(argv[i],"-o")==0) || (strcmp(argv[i],"--output")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			output_file_given=true;
			strcpy(name_out,argv[++i]);
		}
		else usage(argv[0]);
	}
    
  
  
  
  
///////////////////////////////////////////////////////////
///////////////////   OPEN FILES   ////////////////////////
///////////////////////////////////////////////////////////



	if (!input_file_given) {
		fin=stdin;
	}
	else {
		if ( (fin=fopen(name_in,"r"))==NULL)
			report_error("name_in -- fopen: error");
	}


	if (!output_file_given) 
		fout=stdout;
	else {
		if ( (fout=fopen(name_out,"w"))==NULL)
			report_error("name_out -- fopen: error");
	}

  	

///////////////////////////////////////////////////////////
/////////////////   LOADING GRAPH   ///////////////////////
///////////////////////////////////////////////////////////


	fprintf(stderr,"Reading the graph...\n");
	G = graph_from_file(fin);

	fprintf(stderr,"%d vertices, %d edges in the graph\n",G->n,G->m);
	fflush(stderr);
  
	if (fin!=NULL) {
		fclose(fin);
		fin=NULL;
		fprintf(stderr,"Input file closed.\n");
		fflush(stderr);
	}
 

///////////////////////////////////////////////////////////
//////////////////   DATA STRUCTURE   /////////////////////
///////////////////////////////////////////////////////////

	bool* presence = (bool*) malloc(G->n * sizeof(bool));
	int* degre_courant = (int*) malloc(G->n * sizeof(int));
	int *plus_grand_stable = (int*) malloc(G->n * sizeof(int));
	nodl* sommets_stable_courant = (nodl*) malloc(sizeof(nodl) + 100);

	plus_grand_stable = 0;
	sommets_stable_courant->dern = NULL;
	sommets_stable_courant->prem = NULL;

	for(int i = 0; i < G->n; i++) {
		presence[i] = true;
		degre_courant[i] = G->degrees[i];
	}

	int* noeuds_stables_max = (int *) malloc(sizeof(int));
	int* noeuds_stables_courant = (int *) malloc(sizeof(int));
	int* noeuds_restants = (int *) malloc(sizeof(int));

	noeuds_stables_max = 0;
	noeuds_stables_courant = 0;
	noeuds_restants = G->n;

///////////////////////////////////////////////////////////
/////////////////   COMPUTE MIN CUT   /////////////////////
///////////////////////////////////////////////////////////


	fprintf(stderr,"Begin computation.\n");

	int x = indice_degret_courant_minimun(presence, degre_courant, G->n);

	for(int i = 0; i < G->n; i++) {
        if(presence[i]) fprintf(stderr,"%d est TRUE, degré est %d.\n", i, degre_courant[i]);
        if(!presence[i]) fprintf(stderr,"%d est FALSE, degré est %d.\n", i, degre_courant[i]);
    }

	calcul_stable_max(&presence, &degre_courant, &sommets_stable_courant, x, G, &noeuds_stables_max, &noeuds_stables_courant, &noeuds_restants); 
	fprintf(stderr,"après fonction.\n");
	fflush(stderr);


///////////////////////////////////////////////////////////
//////////////////   OUTPUT RESULTS   /////////////////////
///////////////////////////////////////////////////////////


	fprintf(stderr,"Outputing results.\n");

	fprintf(stderr,"Taille du stable maximum: %d.\n", noeuds_stables_max);
	cell* iter = sommets_stable_courant->prem;
	if(iter == NULL) fprintf(stderr,"iter NULL.\n");
    while(iter != NULL) {
		fprintf(stderr,"%d\n", iter->node);
        iter = iter->suiv;
    }

	fflush(stderr);


///////////////////////////////////////////////////////////
////////////   CLOSE FILES AND FREE MEMORY  ///////////////
///////////////////////////////////////////////////////////

	
	if (fout!=NULL) {
		fclose(fout);
		fprintf(stderr,"Output file closed.\n");
		fflush(stderr);
	}

	free_graph(G);
	free (presence);
	free (degre_courant);
	free (plus_grand_stable);
	vider(sommets_stable_courant);
	free_nodl(sommets_stable_courant);

	fprintf(stderr,"Memory freed.\n");
	fflush(stderr);


	return 0;
}

/**************************************************************/
/**************************************************************/
/*************************            *************************/
/*************************  FIN MAIN  *************************/
/*************************            *************************/
/**************************************************************/
/**************************************************************/


