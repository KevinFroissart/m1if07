
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>


///////////////////////////////////////////////////////////
////////////////   UTILITY FUNCTIONS   ////////////////////
///////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// SORTIR DU PROGRAMME AVEC UNE ERREUR
// precondition: s pointe sur une chaine de caractere valide
// postcondition: ecrit la chaine de caractere pointee par s sur la sortie d'erreur standard et sort du programme avec le code d'erreur -1
void report_error(char *s){
  fprintf(stderr,"%s\n",s);
  exit(-1);
}



