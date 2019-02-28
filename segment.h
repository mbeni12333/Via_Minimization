#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include "cell_segment.h"
/*Chaque segment  est defini par le numero du reseau dont il
appartient , ainsi que ses 2 extremites, */
struct cell_segment;
typedef struct segment{

    int NumRes; /* Numero du reseau auquel appartient ce segment*/
    int p1, p2; /* Numero des points aux extremites du segment */
            /* En utilisant la numerotation de T_Pt */
            /* p1 est le point en bas a gauche par rapport a p2*/

    int HouV; /* 0 si Horizontal et 1 si Vertical */

    struct cell_segment *Lintersec; /* Liste des segments en intersection */

} Segment;



/*Cette fonction cree un segment avec tout ses parametres*/
Segment* initialize_segment(int NumRes, int p1, int p2, int HouV);



#endif
