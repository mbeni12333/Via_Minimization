#include "cell_segment.h"


Cell_segment* initialize_cell_segment(Segment* seg){
  Cell_segment* temp = (Cell_segment*)malloc(sizeof(Cell_segment));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation Point\n");
    return NULL;
  }
  // sinon on initilise
  temp->seg = seg;
  temp->suiv = NULL;

  return temp;
}
/*Fonction ajouter_segment*/
int ajouter_segment(Cell_segment** cell_seg, Segment* addme){
    // on cree l'element
    Cell_segment* temp = initialize_cell_segment(addme) ;

    if(!temp){
        fprintf(stderr, "Erreur d'initialisation cell_seg in ajouter_segment\n");
        return 1;
    }
    // si la liste est vide
    if(!(*cell_seg)){
        *cell_seg = temp;
        return 0;
    }else{
        temp->suiv = *cell_seg;
        *cell_seg = temp;
        return 0;
    }
}
/*Fonction qui supprime un segment*/
int supprime_segment(Segment** suppme){return 0;}
/*Fonction pour verifier si liste vide*/
int cell_seg_vide(Cell_segment* cell_seg){
  return cell_seg == NULL;
}
/*Creation de copie*/
Cell_segment* copie_cell_segment(Cell_segment* cell_seg){return NULL;}
/*Afficher une netlist*/
void afficher_cell_segment(Cell_segment* cell_seg, SVGwriter* svg, Netlist* nl){

    printf("\t\tliste:\n\t\t");
    while(cell_seg != NULL){
        afficher_segment(cell_seg->seg, svg, nl);
        printf("->");
        cell_seg = cell_seg->suiv;
    }
    printf("NULL\n");

}
