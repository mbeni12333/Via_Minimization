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
void afficher_segment(Segment* seg, SVGwriter* svg, Netlist* nl){
  char c = (seg->HouV == 0) ? 'H':'V';
  printf("%c(%d,%d)", c, seg->p1, seg->p2);
  if(svg != NULL){
    double xa, xb, ya, yb;
    Point** pt = nl->T_Res[seg->NumRes]->T_Pt;
    xa=pt[seg->p1]->x;
    ya=pt[seg->p1]->y;
    xb=pt[seg->p2]->x;
    yb=pt[seg->p2]->y;
    SVGline(svg, xa, ya, xb, yb);
  }
}
