#include<stdlib.h>
#include<stdio.h>


#ifndef _CELL_SEGMENT_H_
#define _CELL_SEGMENT_H_

#include "segment.h"
/*Ceci est une liste qui vas contenir tout les segments
 qui intersectent avec un certain segment*/
 struct segment;
typedef struct cell_segment{

    struct segment* seg;
    struct cell_segment *suiv;

} Cell_segment;


#endif
