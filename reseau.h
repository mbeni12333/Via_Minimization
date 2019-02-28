#ifndef _RESEAU_H_
#define _RESEAU_H_

#include <stdio.h>
#include <stdlib.h>

#include "cell_segment.h"
#include "point.h"


typedef struct reseau{

    int  NumRes; /* Numero du reseau = Indice dans le tableau T_Res */
    int NbPt;  /* Nombre de points de ce reseau */
    Point* *T_Pt;  /* Tableau de pointeurs sur chaque point de ce reseau */

}Reseau;

Reseau* initilize_reseau(int NumRes, int NbPt);

#endif
