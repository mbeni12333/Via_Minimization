#include "reseau.h"

Reseau* initilize_reseau(int NumRes, int NbPt){
  Reseau* temp = (Reseau*)malloc(sizeof(Reseau));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation Reseau\n");
    return NULL;
  }
  // sinon on initilise
  temp->NumRes = NumRes;
  temp->NbPt = NbPt;
  // on initialise dynamiquement tableau de points
  Point** T_Pt = (Point**)malloc(sizeof(Point*)*NbPt);
  // si il ya un probleme d'Allocation
  if(!T_Pt){
    // liberer ESPACE
    fprintf(stderr, "Erreur Allocation T_PT Reseau\n");
    return NULL;
  }
  // sinon on initilise les pointeur a NULL
  temp->T_Pt = T_Pt;


  // finallement on retourne le pointeur
  return temp;
}
