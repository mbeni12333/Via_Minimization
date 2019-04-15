#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "structs.h"
#include "netlist.h"
#include "point.h"
#include "segment.h"
#include "cell_segment.h"
#include "reseau.h"

// fonctions relative au graph

// fonction de creation de graph
Graph* init_graph(Netlist* nl);
void methode_naiif(Graph* G);
// algorithme principale
void minimize_via(Graph* G);
void bicolore(Graph* G);
void detect_cycle(Graph* G);
// fonction de viz
void vizualize_graph(Graph* G);
// liberation de memoire graph
void free_graph(Graph* G);

#endif
