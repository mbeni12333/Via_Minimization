#include "netlist.h"
#include <string.h>

int main(int argc, char** argv){
  // on verifie le format
  if(argc != 3){
    fprintf(stderr, "Erreur de format, ./%s <NomFichier> <FichierViz>\n", argv[0]);
    return 1;
  }
  // on recupére les parametres
  char* NomFichier = strdup(argv[1]);
  char* FichierViz = strdup(argv[2]);

  //on cree le netlist
  Netlist* netlist = read_net_from_file(NomFichier);
  // on appelle la fonction de visualisation
  visualiser_netlist(netlist, FichierViz);
  // on libere l'espace
  printf("Fin du programe\n");
  return 0;
}
