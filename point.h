#ifndef _POINT_H_
#define _POINT_H_

#include <stdio.h>
#include <stdlib.h>
#include "cell_segment.h"

typedef struct point{

    double x,y;/* Coordonnees du point */
    int num_res;/* Numero du reseau contenant ce point = Index du tableau T_res*/
    Cell_segment* Lincid;/* Liste des segments incidents a ce point */

} Point;


/**************************************************************
*                       Fonction de point                     *
**************************************************************/

/*Fonction d'initialisation*/
Point* initialize_point(double x, double y, int num_res);
/*Creation de copie*/
Point* copie_point(Point* pt);
/*Afficher une netlist*/
void afficher_point(Point* pt,  char* tab);
#endif
