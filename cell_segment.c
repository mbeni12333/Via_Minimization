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
void ajouter_segment_trie(Netlist* nl, Cell_segment** cell_seg, Segment *seg){
  
  Cell_segment * cell = initialize_cell_segment(seg);
  if(!cell){
      return;
  }

  Reseau **T_Res = nl->T_Res; 

  int y = T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

  Cell_segment * current = *cell_seg;
 
  if(!*cell_seg){
      *cell_seg = cell;
  }else{
    if (T_Res[(*cell_seg)->seg->NumRes]->T_Pt[(*cell_seg)->seg->p1]->y>=y){
        cell->suiv = *cell_seg;
        *cell_seg = cell;
    }else{
        current = *cell_seg;
   
        while(!current->suiv && T_Res[current->suiv->seg->NumRes]->T_Pt[current->suiv->seg->p1]->y <= y){
            current = current->suiv;
    }
   
        cell->suiv = current->suiv;
        current->suiv = cell;

    }
  }
}
/*Fonction qui supprime un segment*/
int supprime_segment(Cell_segment** cell_seg, Segment* suppme){
    if(!*cell_seg)return 0;
    Cell_segment* current = *cell_seg;
    

    /*Cas particulier*/
    if(current->seg == suppme){
        *cell_seg = current->suiv;
        free(current);
        return 1;
    }

    while(current->suiv && (current->suiv->seg != suppme)){
        current = current->suiv;
    }

    if(current){
        Cell_segment* temp = current->suiv;
        if(!temp) return 0;

        current = current->suiv->suiv;
        free(temp);
        
        return 1;
    }else{
        return 0;
    }
}
/*Fonction pour verifier si liste vide*/
int cell_seg_vide(Cell_segment* cell_seg){
  return cell_seg == NULL;
}
/*Creation de copie*/
Cell_segment* copie_cell_segment(Cell_segment* cell_seg){return NULL;}
/*nbElem*/
int nbElem(Cell_segment* cell_seg){
  int cpt = 0;
  while(cell_seg != NULL){
    cell_seg = cell_seg->suiv;
    cpt++;
  }
  return cpt;
}
/*Afficher une netlist*/
void afficher_cell_segment(Cell_segment* cell_seg){

    //printf("\t\tliste:\n\t\t");
    while(cell_seg != NULL){
        afficher_segment(cell_seg->seg);
        //printf("->");
        cell_seg = cell_seg->suiv;
    }
    //printf("NULL\n");

}
/*Methodes a voir*/
Cell_segment* prem_segment_apres(Netlist* nl, Cell_segment* cell_seg, double y){
  Reseau** T_Res = nl->T_Res;
  
  while(cell_seg){

      if(T_Res[cell_seg->seg->NumRes]->T_Pt[cell_seg->seg->p1]->y >= y)
        return cell_seg;

      cell_seg = cell_seg->suiv;
  }
  return NULL;
}


Segment * AuDessus(Netlist* nl,Cell_segment* cell_seg, double y){
   //tab des reseau
  Reseau **T_Res = nl->T_Res; 
    // y  de seg
  //int y = T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
    
    
  //while(!cell_seg){
    if(!cell_seg || !cell_seg->suiv){
        return NULL;
    }
    if(T_Res[cell_seg->suiv->seg->NumRes]->T_Pt[cell_seg->suiv->seg->p1]->y >= y){
        return NULL;
    }else{
        return cell_seg->suiv->seg;
    }
}


