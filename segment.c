#include "segment.h"

Segment* initialize_segment(int NumRes, int p1, int p2, int HouV){
  Segment* temp = (Segment*)malloc(sizeof(Segment));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation espace Segment\n");
    return NULL;
  }

  // sinon on initialise les variables
  temp->NumRes = NumRes;// numero du reseau
  temp->p1 = p1; // le premier point
  temp->p2 = p2; // le deuxieme point
  temp->HouV=HouV;// 0 horizontal 1 vertical
  temp->Lintersec = NULL; // il n'y a pas d'intersection pour l'instant

  // et finallement on retourene le pointeur
  return temp;
}
void afficher_segment(Segment* seg){
  char c = (seg->HouV == 0) ? 'H':'V';
  printf("%c", c);
}
