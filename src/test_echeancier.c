#include "structs.h"
#include "echeancier.h"
#include <time.h>
void menu(){
  // les differents tests a faire
}

int main(int argc, char** argv){

    // verification format
    if(argc!=3){
      fprintf(stderr, "Erreur format ./tests_elementaires nom_fichier\n");
      return 1;
    }
    double time;
		int cpt;
    char* file = argv[1];
    Netlist* netlist = read_net_from_file(file);
    //printf("Netlist : %d\n", netlist->NbRes);
    //afficher_netlist(netlist);
    // affichage
    //afficher_netlist(netlist);
    clock_t t = clock();
    // suppresion de l'ESPACE
    //Echeancier* E = creer_echeancier(netlist);
    if(atoi(argv[2]) == 2){
    	cpt = intersect_baleyage_avl(netlist);
		}
    else {
			cpt = intersect_baleyage(netlist);
		}
    clock_t end = clock() - t;
    time = (double)(clock() - t)/CLOCKS_PER_SEC;

    printf("Time needed in cycles=%ld;segments=%d;intersections found=%d\n", end,netlist->nbSeg, cpt);
    //free_echeancier(E);
    return 0;
}
