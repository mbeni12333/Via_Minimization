struct segment;


/*Ceci est une liste qui vas contenir tout les segments
 qui intersectent avec un certain segment*/
typedef struct cell_segment{

    struct segment* seg;
    struct cell_segment *suiv;

} Cell_segment;

/*Chaque segment  est defini par le numero du reseau dont il 
appartient , ainsi que ses 2 extremites, */
typedef struct segment{

    int NumRes; /* Numero du reseau auquel appartient ce segment*/
    int p1, p2; /* Numero des points aux extremites du segment */
            /* En utilisant la numerotation de T_Pt */
            /* p1 est le point en bas a gauche par rapport a p2*/


    int HouV; /* 0 si Horizontal et 1 si Vertical */    

    struct cell_segment *Lintersec; /* Liste des segments en intersection */

} Segment;


typedef struct point{

    double x,y;/* Coordonnees du point */
    int num_res;/* Numero du reseau contenant ce point = Index du tableau T_res*/
    Cell_segment* Lincid;/* Liste des segments incidents a ce point */

} Point;


typedef struct reseau{

    int  NumRes; /* Numero du reseau = Indice dans le tableau T_Res */
    int NbPt;  /* Nombre de points de ce reseau */
    Point* *T_Pt;  /* Tableau de pointeurs sur chaque point de ce reseau */

}Reseau;


typedef struct netlist {
    int NbRes; /* Nombre de reseaux*/
    Reseau* *T_Res; /* Tableau pointant sur chaque reseau*/
}Netlist;


/* Ensemble des fonction netlist pour parser les benchmarks*/

/*Cette fonction cree un segment avec tout ses parametres*/
Segment* initialize_segment(int NumRes, int p1, int p2, int HouV);

/*Ensembles de fonction sur la liste cell_segment*/

/*Cette fonction permet de creer une Netlist avec NbRes reseaux*/
Netlist* initialize_netlist(int NbRes);
/*Cette fonction permet de lire un reseau*/
Netlist* read_net_from_file(char* file);

