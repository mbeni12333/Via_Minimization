#include "structs.h"
#include "detect_intersection.h"
#include <time.h>
void menu(){
  // les differents tests a faire
}

int main(int argc, char** argv){

    // verification format
    if(argc!=2){
      fprintf(stderr, "Erreur format ./tests_elementaires nom_fichier\n");
      return 1;
    }
    double time;
    char* file = argv[1];
    Netlist* netlist = read_net_from_file(file);
    //printf("Netlist : %d\n", netlist->NbRes);
    //afficher_netlist(netlist);
    // affichage
    //afficher_netlist(netlist);
    clock_t t = clock();
    // suppresion de l'ESPACE
    int intersect = intersect_naif(netlist);
    clock_t end = clock() - t;
    time = (double)(clock() - t)/CLOCKS_PER_SEC;
    printf("Time needed in cycles=%ld;segments=%d;intersections found=%d\n", end,netlist->nbSeg, intersect);
    return 0;
}
