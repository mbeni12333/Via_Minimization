#include<stdlib.h>
#include<stdio.h>


#ifndef _AVL_H_
#define _AVL_H_

#include "segment.h"
#include "SVGwriter.h"
#include "netlist.h"

/*Structure AVL qui contient l'ensemble des informations
dans un arbre binaire de recherche AVL*/
struct segment;
struct netlist;
typedef struct AVL{
  Segment* seg;
  double clef;  
  int hauteur;
  AVL* fils_gauche;
  AVL* fils_droite;
}AVL;

/*Fonction d'initialisation de la structure*/
AVL* Ajout_feuille(Segment * seg, Netlist *n);
/*Calcule de la hauteur d'un arbre*/
int hauteur(*AVL ab);
/*Ajout d'un segment dans l'arbre AVL*/
void ajout_segment_AVL(AVL* ab, Netlist * n);
/*Suppression d'un segment dans l'arbre AVL*/
void suppression_segment_AVL(AVL* ab, Netlist* n);
/*Liberation de l'espace alloué pour l'AVL*/
void free_AVL(AVL *ab);
//max
int max(int a,int b);
//Rotation Droite
void Rotation_droite(AVL *ab);
//Rotation Gauche 
void Rotation_gauche(AVL *ab);