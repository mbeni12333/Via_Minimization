
#ifndef _NETLIST_H_
#define _NETLIST_H_

#include<stdio.h>
#include<stdlib.h>
#include "segment.h"
#include "point.h"
#include "cell_segment.h"
#include "reseau.h"


typedef struct netlist {
    int NbRes; /* Nombre de reseaux*/
    Reseau* *T_Res; /* Tableau pointant sur chaque reseau*/
}Netlist;


/***********************************************************
* Ensemble des fonction netlist pour parser les benchmarks *
***********************************************************/

/*Cette fonction permet de creer une Netlist avec NbRes reseaux*/
Netlist* initialize_netlist(int NbRes);
/*Cette fonction permet de lire un reseau*/
Netlist* read_net_from_file(char* file);
/*Creation de copie*/
Netlist* copie_netlist(Netlist* nl);
/*Afficher une netlist*/
void afficher_netlist(Netlist* nl);


#endif
