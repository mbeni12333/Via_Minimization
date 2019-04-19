#include "structs.h"
#include "graph.h"
#include "echeancier.h"
#include "netlist.h"
#include "stdio.h"
#include <time.h>


int main(int argc, char** argv){

    // verification format
    if(argc!=2){
      fprintf(stderr, "Erreur format ./test_graph nom_fichier\n");
      return 1;
    }
    double time;
		int cpt;
    char* file = argv[1];
    // lire l'instance
    Netlist* netlist = read_net_from_file(file);

 

    // detection intersections
    int nb_intersect = intersect_baleyage_avl(netlist);

    // creation du graph
    Graph* g = init_graph(netlist);

    // sauvegarder_graph_dot
    //tests
       //Segment* sg =;;
    /*int i=0;
    for(i=0; i<netlist->nbSeg;i++){
          //if(!sg)printf("This is whyyy\n");
            printf("nbSeg = %d, num dernier seg: %d\n", i,  g->T_Seg[i]->numSg);
    }
*/

  methode_naiif(g, netlist);
  afficher_graph(netlist, g, "test_graph");

    return 0;
}
