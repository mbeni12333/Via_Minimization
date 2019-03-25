#ifndef _DETECT_INTERSECTION_H_
#define _DETECT_INTERSECTION_H_

#include "structs"

/*Fonction auxiliere*/
int intersection(Netlist* nl, Segment *s1, Segment *s2);
Segment** tableau_segments(Netlist* nl);
int nbSeg(Netlist* nl);
/*Algorithms*/
int intersect_naif(Netlist* nl);



/*Fonction standard*/
void sauvgarder_intersections(Netlist* nl,char* nomfichier);
#endif
