#include "structs.h"
#include "echeancier.h"
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
        sauvegarde_de_la_netlist(netlist, "test_sauvegarde");
    clock_t t = clock();
    // suppresion de l'ESPACE
    //Echeancier* E = creer_echeancier(netlist);
    int cpt = intersect_baleyage(netlist);
    time = (double)(clock() - t)/CLOCKS_PER_SEC;

    printf("Time needed = %.5f s, intersections found = %d\n", time, cpt);
    //free_echeancier(E);
    return 0;
}
