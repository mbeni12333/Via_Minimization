#include "structs.h"

#ifndef _ECHEANCIER_H_
#define _ECHEANCIER_H_

#include "cell_segment.h"
#include "netlist.h"
#include "segment.h"

/**************************************************************
*                       Fonction de echeancier              *
**************************************************************/
/*Fonction d'initialisation d'une cellule*/
Extremite* init_extremite(double x, int VouGouD, Segment* seg, int NumPt);
Echeancier* init_elem_echeancier(Extremite* ext);
Echeancier* ajouter_segment_echeancier(Netlist* nl, Segment* seg);
/*Fonction creation netlist*/
Echeancier* creer_echeancier(Netlist* nl, int* cpt);
/*Trie d'Echeancier*/
int compare_extremite(Extremite* exta, Extremite* extb);
void split_liste(Echeancier* E, Echeancier** a, Echeancier** b);
Echeancier* merge(Echeancier* a, Echeancier* b);
void merge_sort(Echeancier** E);
/*Liberer echeancier*/
void free_echeancier(Echeancier* E);
/*Affichage echeancier pour debogage*/

int intersect_baleyage(Netlist* nl);

void afficher_echeancier(Echeancier* E);

#endif
