#include<stdlib.h>
#include<stdio.h>


#ifndef _CELL_SEGMENT_H_
#define _CELL_SEGMENT_H_

#include "segment.h"
/*Ceci est une liste qui vas contenir tout les segments
 qui intersectent avec un certain segment*/
struct segment;
typedef struct cell_segment{

    struct segment* seg;
    struct cell_segment *suiv;

} Cell_segment;

/**************************************************************
*                       Fonction de Cell_segment              *
**************************************************************/
/*Fonction d'initialisation d'une cellule*/
Cell_segment* initialisation(struct segment* seg);
/*Fonction ajouter_segment*/
int ajouter_segment(Cell_segment** cell_seg, struct segment* addme);
/*Fonction qui supprime un segment*/
int supprime_segment(struct segment** suppme);
/*Fonction pour verifier si liste vide*/
int cell_seg_vide(Cell_segment* cell_seg);
/*Creation de copie*/
Cell_segment* copie_cell_segment(Cell_segment* cell_seg);
/*Afficher une netlist*/
void afficher_cell_segment(Cell_segment* cell_seg, char* tab);
#endif
