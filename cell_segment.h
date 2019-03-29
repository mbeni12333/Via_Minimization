#include "structs.h"

#ifndef _CELL_SEGMENT_H_
#define _CELL_SEGMENT_H_

#include "segment.h"

/**************************************************************
*                       Fonction de Cell_segment              *
**************************************************************/
/*Fonction d'initialisation d'une cellule*/
Cell_segment* initialisation(Segment* seg);
/*Fonction ajouter_segment*/
int ajouter_segment(Cell_segment** cell_seg, Segment* addme);
/*Fonction qui supprime un segment*/
int supprime_segment(Cell_segment** cell_seg, Segment* suppme);
/*nbElem*/
int nbElem(Cell_segment* cell_seg);
/*Fonction pour verifier si liste vide*/
int cell_seg_vide(Cell_segment* cell_seg);
/*Creation de copie*/
Cell_segment* copie_cell_segment(Cell_segment* cell_seg);
/*Afficher une cell segment*/
void ajouter_segment_trie(Netlist* nl, Cell_segment** cell_seg, Segment *seg);
void afficher_cell_segment(Cell_segment* cell_seg);
Cell_segment* prem_segment_apres(Netlist* nl, Cell_segment* cell_seg, double y);
Segment * AuDessus(Netlist* nl,  Cell_segment* cell_seg, double y);
/*Liberation espace cell_segment*/
//void free_cell_segment(Cell_segment* cell_seg);
#endif
