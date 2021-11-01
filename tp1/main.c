
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

	int i;



///////////////////////////////////////////////////////////
////////////////   PARSE COMMAND LINE   ///////////////////
///////////////////////////////////////////////////////////


	// default values
	char name_in[100]="";
	char name_out[100]="";
	int input_file_given=0;
	int output_file_given=0;

	// user's values
  
	for (i=1; i<argc; i++) {
		if ((strcmp(argv[i],"-h")==0) || (strcmp(argv[i],"--help")==0) ) {
			usage(argv[0]);     
		}
		else if ((strcmp(argv[i],"-i")==0) || (strcmp(argv[i],"--input")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			input_file_given=1;
			strcpy(name_in,argv[++i]);
		}
		else if ((strcmp(argv[i],"-o")==0) || (strcmp(argv[i],"--output")==0) ) {
			if (i==argc-1)
				usage(argv[0]);
			output_file_given=1;
			strcpy(name_out,argv[++i]);
		}
		else usage(argv[0]);
	}
    
  
  
  
  
///////////////////////////////////////////////////////////
///////////////////   OPEN FILES   ////////////////////////
///////////////////////////////////////////////////////////



	if (input_file_given==0) {
		fin=stdin;
	}
	else {
		if ( (fin=fopen(name_in,"r"))==NULL)
			report_error("name_in -- fopen: error");
	}


	if (output_file_given==0) 
		fout=stdout;
	else {
		if ( (fout=fopen(name_out,"w"))==NULL)
			report_error("name_out -- fopen: error");
	}
	


///////////////////////////////////////////////////////////
/////////////////   LOADING GRAPH   ///////////////////////
///////////////////////////////////////////////////////////

	graph* graph = graph_from_file(fin);
	int nb_sommet = graph->n;
	int nb_arete = graph->m;
	fprintf(stderr, "Nombre de sommets : %d\nNombre d'arêtes : %d\n", nb_sommet, nb_arete);
	free_graph(graph);

///////////////////////////////////////////////////////////
//////////////////   DATA STRUCTURE   /////////////////////
///////////////////////////////////////////////////////////

	int* identifiant_groupe = (int*)malloc(nb_sommet * sizeof(int)); //On donne à chaque sommet-1 son identifiant de groupe, id_group = id_sommet_chef
	nodl* liste_sommets_groupe = (nodl*)malloc(nb_sommet * sizeof(nodl)); // On donne à chaque groupe la liste des sommets qui le compose, id_group = id_sommet_chef, il y aura des cases vides
	int* nb_sommets_groupe = (int*)malloc(nb_sommet * sizeof(int)); //Pour chaque groupe, on associe une taille, pour les sommets qu'on fusionne on pourra leur mettre 0 ou -1

	int itr;
	for(itr = 0; itr < nb_sommet; itr++) {
		identifiant_groupe[itr] = itr;
		liste_sommets_groupe[itr].dern = NULL;
		liste_sommets_groupe[itr].prem = NULL;
		inserer_en_tete(itr, &liste_sommets_groupe[itr]);
		nb_sommets_groupe[itr] = 1;
	}

///////////////////////////////////////////////////////////
/////////////////   COMPUTE MIN CUT   /////////////////////
///////////////////////////////////////////////////////////

	fprintf(stderr,"Begin computation.\n");
	fflush(stderr);


	int itr2;
	for(itr2 = 0; itr2 < nb_sommet; itr2++) {
		fprintf(stderr,"pos:%d id_groupe:%d\n", itr2, identifiant_groupe[itr2]);
		if(nb_sommets_groupe[itr2] != 0) {
			fprintf(stderr, "Groupe %d : %d sommets\n", itr2, nb_sommets_groupe[itr2]);
		}
	}
	int un = 2;
	int deux = 4;

	int lead;
	int fusionne;
	if(nb_sommets_groupe[un] < nb_sommets_groupe[deux]) {
		lead = deux;
		fusionne = un;
	} else {
		lead = un;
		fusionne = deux;
	}

	contraction_simulee(identifiant_groupe, liste_sommets_groupe, nb_sommets_groupe, 2, 4);
	contraction_simulee(identifiant_groupe, liste_sommets_groupe, nb_sommets_groupe, 2, 6);



///////////////////////////////////////////////////////////
//////////////////   OUTPUT RESULTS   /////////////////////
///////////////////////////////////////////////////////////


	fprintf(stderr,"\nOutputing results.\n");
	for(itr2 = 0; itr2 < nb_sommet; itr2++) {
		fprintf(stderr,"pos:%d id_groupe:%d\n", itr2, identifiant_groupe[itr2]);
		if(nb_sommets_groupe[itr2] != 0) {
			fprintf(stderr, "Groupe %d : %d sommets\n", itr2, nb_sommets_groupe[itr2]);
		}
	}
	fflush(stderr);







///////////////////////////////////////////////////////////
////////////   CLOSE FILES AND FREE MEMORY  ///////////////
///////////////////////////////////////////////////////////



	if (fin!=NULL) {
		fclose(fin);
		fprintf(stderr,"Input file closed.\n");
		fflush(stderr);
	}
	
	if (fout!=NULL) {
		fclose(fout);
		fprintf(stderr,"Output file closed.\n");
		fflush(stderr);
	}





	return 0;
}

/**************************************************************/
/**************************************************************/
/*************************            *************************/
/*************************  FIN MAIN  *************************/
/*************************            *************************/
/**************************************************************/
/**************************************************************/


