#include "structs.h"

#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "point.h"
#include "segment.h"
#include "cell_segment.h"
#include "reseau.h"
#include "entree_sortie.h"

/***********************************************************
* Ensemble des fonction netlist pour parser les benchmarks *
***********************************************************/

/*Cette fonction permet de creer une Netlist avec NbRes reseaux*/
Netlist* initialize_netlist(int NbRes);
/*Cette fonction permet de lire un reseau*/
Netlist* read_net_from_file(char* file);
/*Tableau de segments*/
Segment** tableau_segments(Netlist* nl);
/*Tableau de points*/
Point** tableau_points(Netlist* nl);
/*Nombre de segment de la netlist*/
int nbSeg(Netlist* nl);
/*Creation de copie*/
Netlist* copie_netlist(Netlist* nl);
/*Liberation de la memoire*/
void free_netlist(Netlist* nl);
/*Enregistrer netlist dans un fichier.net*/
void sauvegarder_netlsit(Netlist* nl);
/*Afficher une netlist*/
void afficher_netlist(Netlist* nl);
/*Enregister les intersesction dans un fichier .init*/
void sauvegarder_intersections(Netlist* nl, char* nomFichier);
/*Charger les intersections*/
void charger_intersections(Netlist* nl, char* nomFichier);
/*Visualisation Netlist*/
void visualiser_netlist(Netlist* nl, char* nomFichier);


#endif
