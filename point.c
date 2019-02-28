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
