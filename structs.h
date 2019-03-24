#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SVGwriter.h"
/*Structure de Point*/
typedef struct point{

    double x,y;/* Coordonnees du point */
    int num_res;/* Numero du reseau contenant ce point = Index du tableau T_res*/
    struct cell_segment* Lincid;/* Liste des segments incidents a ce point */

} Point;
struct segment;
struct cell_segment;
/*Chaque segment  est defini par le numero du reseau dont il
appartient , ainsi que ses 2 extremites, */


typedef struct segment{

    int NumRes; /* Numero du reseau auquel appartient ce segment*/
    int p1, p2; /* Numero des points aux extremites du segment */
            /* En utilisant la numerotation de T_Pt */
            /* p1 est le point en bas a gauche par rapport a p2*/

    int HouV; /* 0 si Horizontal et 1 si Vertical */
    int printed;
    struct cell_segment *Lintersec; /* Liste des segments en intersection */

} Segment;

/*Ceci est une liste qui vas contenir tout les segments
 qui intersectent avec un certain segment*/

typedef struct cell_segment{

    struct segment* seg;
    struct cell_segment *suiv;

} Cell_segment;
/*Structure de reseaux*/
typedef struct reseau{

    int  NumRes; /* Numero du reseau = Indice dans le tableau T_Res */
    int NbPt;  /* Nombre de points de ce reseau */
    struct point* *T_Pt;  /* Tableau de pointeurs sur chaque point de ce reseau */

}Reseau;
/*Structure principale*/
typedef struct netlist {
    int NbRes; /* Nombre de reseaux*/
    struct reseau* *T_Res; /* Tableau pointant sur chaque reseau*/
}Netlist;

/*Variable Globales utile*/

/*Netlist global qui sera utilise tout le temps sauf si precisé*/
extern Netlist* netlist_globale;
/*SVGwriter global qui sera utilise tout le temps sauf si precisé*/
extern SVGwriter img;

#endif
