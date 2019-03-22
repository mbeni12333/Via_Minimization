#include "netlist.h"
#include "reseau.h"
#include "cell_segment.h"
#include "point.h"
#include "segment.h"

void menu(){
  // les differents tests a faire
}

int main(int argc, char** argv){

    // verification format
    if(argc!=2){
      fprintf(stderr, "Erreur format ./tests_elementaires nom_fichier\n");
      return 1;
    }
    char* file = argv[1];
    Netlist* netlist = read_net_from_file(file);

    // affichage
    afficher_netlist(netlist, NULL);

    // suppresion de l'ESPACE

    return 0;
}
