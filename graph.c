#include "graph.h"
SVGwriter img;
// fonction de creation de graph
Graph* init_graph(Netlist* nl){
  // on assume que la netlist est complette
  // ok alors on veut avoir un tableau des noeud segment
  // et un autre sur les noeud points
  Segment** T_Seg = tableau_segments(nl);
  Point** T_Pt = tableau_points(nl);

  Graph* g = (Graph*)malloc(sizeof(Graph));
  g->T_Seg = T_Seg;
  g->T_Pt = T_Pt;
  //

  return g;
}
void afficher_graph(Netlist* nl, Graph* g, char* nomFichier){
  int i;
  SVGinit(&img, nomFichier, nl->xmin, nl->ymin, nl->xoffsef, nl->yoffset);
  SVGlineRandColor(&img);
  SVGgroup(&img);
  for(i=0; i<nl->nbSeg;i++){
    if(g->T_Seg[i]->HouV){
       afficher_segment(g->T_Seg[i]);
       //printf("H\n");
    }
  }
  SVGgroup_end(&img);

  SVGlineRandColor(&img);
  SVGgroup(&img);
  for(i=0; i<nl->nbSeg;i++){
    if(!(g->T_Seg[i]->HouV)){
       afficher_segment(g->T_Seg[i]);
       //printf("V\n");
    }
  }
  SVGgroup_end(&img);
  SVGfinalize(&img);
}
void affect_via(Netlist* nl, Graph* g){
  return;
}
void methode_naiif(Graph* G){
  return;
}
// algorithme principale
void minimize_via(Graph* G){
  return;
}
void bicolore(Graph* G){
  return;
}
void detect_cycle(Graph* G){
  return;
}
// fonction de viz
void vizualize_graph(Graph* G){
  return;
}
// liberation de memoire graph
void free_graph(Graph* G){
  return;
}
