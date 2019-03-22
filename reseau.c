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

void afficher_point(Reseau* rs, char* tab = ""){
    if(rs == NULL){
      fprintf(stderr, "Netlist Vide !");
      return;
    }
  // on affiche tout les points
  int i;
  Printf("Affichage de Reseau %d (%d Points) : \n", rs->NumRes, rs->NbPt);
  for(i=0; rs->NbPt; i++){
    // on affiche le reseau i (reste a savoir ) 
    afficher_point(rs->T_Pt[i], "\t");
  }
}