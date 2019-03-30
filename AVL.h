

#ifndef _AVL_H_
#define _AVL_H_

#include<stdlib.h>
#include<stdio.h>
#include"detect_intersection.h"

#include"structs.h"
#include "segment.h"
#include "SVGwriter.h"
#include "netlist.h"

/*Structure AVL qui contient l'ensemble des informations
dans un arbre binaire de recherche AVL*/


/*Fonction d'initialisation de la structure*/
AVL* Ajout_feuille(Segment * seg, Netlist *n);
/*Ajout d'un segment dans l'arbre AVL*/
void Ajout_segment_AVL(AVL** ab, Segment* s, Netlist * n);
/*Suppression d'un segment dans l'arbre AVL*/
void Suppression_segment_AVL(AVL **ab, Segment* s , Netlist* n);
/*Liberation de l'espace alloué pour l'AVL*/
void free_AVL(AVL *ab);
//Rotation Droite
void Rotation_droite(AVL **ab);
//Rotation Gauche
void Rotation_gauche(AVL **ab);
//Enlever le minimum
AVL* enleve_min(AVL *ab);

void equilibrer(AVL **ab);
#endif
