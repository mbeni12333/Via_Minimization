

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
void free_AVL(AVL **ab);
//Rotation Droite
void Rotation_droite(AVL **ab);
//Rotation Gauche
void Rotation_gauche(AVL **ab);
//recupre le minimum d'un arbre
AVL* recup_min(AVL **ab);
//Hauteur de l'arbre/noeud
int hauteur(AVL* ab);
//Difference de hauteur entre deux sous arbres
int getDiff(AVL *ab);
// recuperer premeir elem > y1 < y2
AVL* prem_segment_avl(AVL* a, double y1, double y2);
Cell_segment* avl2list(AVL* a);
// convert avl to cell segment
// affichage
void afficher_AVL(AVL* a);
// fonction qui sert a rien
void equilibrer(AVL **ab);
#endif
