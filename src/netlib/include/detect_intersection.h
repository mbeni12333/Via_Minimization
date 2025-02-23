#ifndef _DETECT_INTERSECTION_H_
#define _DETECT_INTERSECTION_H_

#include "structs.h"
#include "netlist.h"
/*Fonction auxiliere*/
int intersection(Netlist* nl, Segment *s1, Segment *s2);
/*Algorithms*/
int intersect_naif(Netlist* nl);

double min(double x, double y);
double max(double x, double y);

/*Fonction standard*/
void sauvgarder_intersections(Netlist* nl,char* nomfichier);
#endif
