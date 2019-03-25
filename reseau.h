#ifndef _RESEAU_H_
#define _RESEAU_H_

#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"
#include "cell_segment.h"
#include "point.h"
#include "SVGwriter.h"
struct netlist;
struct point;
typedef struct reseau{

    int  NumRes; /* Numero du reseau = Indice dans le tableau T_Res */
    int NbPt;  /* Nombre de points de ce reseau */
    struct point* *T_Pt;  /* Tableau de pointeurs sur chaque point de ce reseau */

}Reseau;
/***********************************************************
* Ensemble des fonction Reseaux                            *
***********************************************************/
/*Initialisation de reseau*/
Reseau* initilize_reseau(int NumRes, int NbPt);
/*Affichage de reseau*/
void afficher_reseau(Reseau* res, SVGwriter* svg, struct netlist* nl);
/*Liberetion espace mempoire reseau*/
//void free_reseau(Reseau* res);
#endif
