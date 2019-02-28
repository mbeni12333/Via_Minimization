#include "netlist.h"

Netlist* initialize_netlist(int NbRes){
  Netlist* temp = (Netlist*)malloc(sizeof(Netlist));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation Netlist\n");
    return NULL;
  }
  // sinon on initilise
  temp->NbRes = NbRes;
  // on cree le tableau de reseax;
  Reseau** T_Res = (Reseau**)malloc(sizeof(Reseau*)*NbRes);
  // erreur
  if(!T_Res){
    // free
    fprintf(stderr, "Erreur Allocation T_Res\n");
    return NULL;
  }// sinon

  // mettre case a NULL
  return temp;
}
