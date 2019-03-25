#include<stdlib.h>
#include<stdio.h>


#ifndef _CELL_SEGMENT_H_
#define _CELL_SEGMENT_H_

#include "segment.h"
#include "SVGwriter.h"
#include "netlist.h"
/*Ceci est une liste qui vas contenir tout les segments
 qui intersectent avec un certain segment*/
struct segment;
struct netlist;
typedef struct cell_segment{

    struct segment* seg;
    struct cell_segment *suiv;

} Cell_segment;

/**************************************************************
*                       Fonction de Cell_segment              *
**************************************************************/
/*Fonction d'initialisation d'une cellule*/
Cell_segment* initialisation(Segment* seg);
/*Fonction ajouter_segment*/
int ajouter_segment(Cell_segment** cell_seg, Segment* addme);
/*Fonction qui supprime un segment*/
int supprime_segment(Segment** suppme);
/*nbElem*/
int nbElem(Cell_segment* cell_seg);
/*Fonction pour verifier si liste vide*/
int cell_seg_vide(Cell_segment* cell_seg);
/*Creation de copie*/
Cell_segment* copie_cell_segment(Cell_segment* cell_seg);
/*Afficher une cell segment*/
void afficher_cell_segment(Cell_segment* cell_seg, SVGwriter* svg, struct netlist* nl);
/*Liberation espace cell_segment*/
//void free_cell_segment(Cell_segment* cell_seg);
#endif
