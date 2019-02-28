#include <stdio.h>
#include <stdlib.h>
#include "cell_segment.h"

#ifndef _POINT_H_
#define _POINT_H_

typedef struct point{

    double x,y;/* Coordonnees du point */
    int num_res;/* Numero du reseau contenant ce point = Index du tableau T_res*/
    Cell_segment* Lincid;/* Liste des segments incidents a ce point */

} Point;

#endif
