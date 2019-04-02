#include "structs.h"
#include "netlist.h"
#include "AVL.h"
#include "cell_segment.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char** argv){

    if(argc != 2){
        fprintf(stderr, "Erreur format, %s <nom_ficiher>\n", argv[0]);
        return 1;
    }

    // lecture des n elements
    Netlist* netlist = read_net_from_file(argv[1]);
    // creation du tab des segments
    Segment** T_Seg = tableau_segments(netlist);

    int i = 0;

    AVL* Head = NULL;



    for(i=0; i<netlist->nbSeg; ++i){
        Ajout_segment_AVL(&Head, T_Seg[i], netlist);
        printf("Segment %d ajouté\n", i);
    }
    afficher_AVL(Head);
    printf("\n");
    Suppression_segment_AVL(&Head, Head->seg, netlist);
    afficher_AVL(Head);
    printf("\n");
    return 0;
}