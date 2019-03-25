#include "point.h"

Point* initialize_point(double x, double y, int num_res){
  Point* temp = (Point*)malloc(sizeof(Point));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation Point\n");
    return NULL;
  }
  // sinon on initilise
  temp->x = x;
  temp->y = y;
  temp->num_res = num_res;
  temp->Lincid = NULL; // pour l'instant

  return temp;
}

void afficher_point(Point* pt, SVGwriter* svg, Netlist* nl){
    if(pt == NULL){
      fprintf(stderr, "point vide Vide !");
      return;
    }
  // on affiche tout les points
  printf("\tPoint (x=%.1f, y=%.1f) : \n",pt->x, pt->y);
  if(svg != NULL){
    SVGpoint(svg, pt->x, pt->y);
  }
  afficher_cell_segment(pt->Lincid, svg, nl);
}
