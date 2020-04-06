#include "structs.h"

#ifndef _POINT_H_
#define _POINT_H_

#include "cell_segment.h"
/**************************************************************
*                       Fonction de point                     *
**************************************************************/

/*Fonction d'initialisation*/
Point* initialize_point(double x, double y, int num_res, int numPt);
/*Creation de copie*/
Point* copie_point(Point* pt);
/*Afficher une netlist*/
void afficher_point(Point* pt);
/*Liberation espace point*/
void free_point(Point* p);
#endif
