#include "structs.h"

#ifndef _RESEAU_H_
#define _RESEAU_H_



/***********************************************************
* Ensemble des fonction Reseaux                            *
***********************************************************/
/*Initialisation de reseau*/
Reseau* initilize_reseau(int NumRes, int NbPt);
/*Affichage de reseau*/
void afficher_reseau(Reseau* res);
/*Liberetion espace mempoire reseau*/
//void free_reseau(Reseau* res);
#endif
