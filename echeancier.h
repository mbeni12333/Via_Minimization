#include "structs.h"

#ifndef _ECHEANCIER_H_
#define _ECHEANCIER_H_

#include "cell_segment.h"
#include "segment.h"

/**************************************************************
*                       Fonction de echeancier              *
**************************************************************/
/*Fonction d'initialisation d'une cellule*/
Extremite* initialisation(Segment* seg);
/*Fonction creation netlist*/
Echeancier* creer_echeancier(Netlist* nl);
/*Trie d'Echeancier*/
Echeancier* tri_echeancier(Echeancier* E);

#endif
