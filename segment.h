#include "structs.h"

#ifndef _SEGMENT_H_
#define _SEGMENT_H_


/***********************************************************
* Ensemble des fonction segment                            *
***********************************************************/

/*Cette fonction cree un segment avec tout ses parametres*/
Segment* initialize_segment(int NumRes, int p1, int p2, int HouV);
/*Affichage de segment*/
void afficher_segment(Segment* seg);
/*Liberation espace memoire segment;*/
void free_segment(Segment* seg);
#endif
