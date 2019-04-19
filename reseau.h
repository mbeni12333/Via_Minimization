#include "structs.h"

#ifndef _RESEAU_H_
#define _RESEAU_H_

#include "netlist.h"

/***********************************************************
* Ensemble des fonction Reseaux                            *
***********************************************************/
/*Initialisation de reseau*/
Reseau* initilize_reseau(int NumRes, int NbPt, int NbSeg);
/*Affichage de reseau*/
void afficher_reseau(Reseau* res);
/*Liberetion espace mempoire reseau*/
//void free_reseau(Reseau* res);
#endif
