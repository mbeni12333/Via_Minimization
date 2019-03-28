#include<stdio.h>
#include<stdlib.h>
#include"AVL.h"
#include "netlist.h"

void affiche_AVL(AVL* ab){
    if(ab == NULL)
        return;
    affiche_AVL(ab->fils_gauche);
    printf("-> %d",ab->clef);
    affiche_AVL(ab->fils_droit);
}

int main(){
    Segment *s1=initialize_segment(2,1,2,0);
    Segment *s2=initialize_segment(2,1,3,0);

    AVL * ab;
    Ajout_feuille(s1,read_net_from_file("test.net"));
    Ajout_feuille(s2,read_net_from_file("test.net"));
    affiche_AVL(ab);
    Suppression-feuille(s2,read_net_from_file("test.net"));
    affiche_AVL(ab);

    return 0;
}