#include "detect_intersection.h"
/*Fonction auxiliere*/
int min(int x, int y){
  return x < y ? x:y;
}
int max(int x, int y){
  return x > y ? x:y;
}
int intersection(Netlist* nl, Segment *s1, Segment *s2){
  // rien a faire
  if(!nl || !s1 || !s2){
    return 0;
  }
  // seulment si les il ne sont pas chevauché, ou ne sont pas du meme reseau
  if((s1->HouV != s2->HouV) && (s1->NumRes != s2->NumRes)){
     Reseau* r1 = nl->T_Res[s1->NumRes];
     Reseau* r2 = nl->T_Res[s2->NumRes];
     Point * p1 = r1->T_Pt[s1->p1],
           * p2 = r1->T_Pt[s1->p2],
           * p3 = r2->T_Pt[s2->p1],
           * p4 = r2->T_Pt[s2->p2];


     double  xv,
             xh1,
             xh2,
             yh,
             yv1,
             yv2;
     // a revoire dans les tests , prendre le max
     // comme on sait pas si les points sont de gauche a droite
     // il se peut qu'un point sois dans l'ordre inverse
     // et alors la comparaison ne marchera pas
     if(s1->HouV){
        // s1 est le vertical
        xv = p1->x;
        yh = p3->y;

        yv1 = p1->y;
        yv2 = p2->y;
        xh1 = p3->x;
        xh2 = p4->x;

     }else{
       // si s2 est le vertical
       xv = p3->x;
       yh = p1->y;

       yv1 = p3->y;
       yv2 = p4->y;
       xh1 = p1->x;
       xh2 = p2->x;
     }

     return (xv >= min(xh1, xh2) && xv <= max(xh2, xh1) && yh <= max(yv1,yv2) && yh >= min(yv1,yv2));
  }
  return 0;
}
Segment** tableau_segments(Netlist* nl){
  if(!nl)return NULL;
  int nbseg =  nbSeg(nl);

  Segment** T_Seg = (Segment**)malloc(sizeof(Segment*)*nbseg);
  if(!T_Seg){
    fprintf(stderr, "Erreur allocation tableau de segment");
    return NULL;
  }
  // sinon si tout va bien, on parcours tout le netist et on remplit le tableau_segments
  int i = 0;
  int j = 0;
  int cpt = 0;
  Reseau** T_Res = nl->T_Res;
  Reseau* current_reseau;
  for(i=0; i < nl->NbRes; i++){
    // on fixe le reseau actuelle
    current_reseau = T_Res[i];
    Point** T_Pt = current_reseau->T_Pt;
    // on parcours tout les points
    for(j=0; j<current_reseau->NbPt; j++){
      // on ajoute l'element dans le tableau a la case
      // compteur
      Point* current_point = T_Pt[j];

      Cell_segment* current_liste = current_point->Lincid;
      Segment* current_seg;
      // on parcour la liste des segments
      while(current_liste != NULL){
        // on ajoute l'element dans le tabeleau et on incremente l'indice
        // si le segment n'est pas deja present
        current_seg = current_liste->seg;

        if(!current_seg->printed){
          T_Seg[cpt++] = current_seg;
          current_seg->printed = 1;
        }
        //printf("Cpt = %d\n", cpt);
        current_liste = current_liste->suiv;
      }
    }

  //printf("NbSeg = %d\n", nbseg);
  }
  return T_Seg;
}
int nbSeg(Netlist* nl){
  return nl->nbSeg;
}
/*Algorithms*/
int intersect_naif(Netlist* nl){
  // on construit le tableau des segment a partir de nl
  Segment** T_Seg = tableau_segments(nl);
  int nbseg = nbSeg(nl);
  // erreur
  if(!T_Seg){
    return 0;
  }
  // sinon on parcour tout le tableau et on compare les seg deux a deux
  int i = 0;
  int j = 0;
  int cpt = 0;
  for(i=0; i<nbseg; i++){
    for(j=i+1; j<nbseg; j++){
      // on commence par i+1 pour eviter ne pas refaire les cas deja
      // traité
      if(intersection(nl, T_Seg[i], T_Seg[j])){
        // la il faut apeender seg j dans sei et seg i dans seg j
        ajouter_segment(&T_Seg[i]->Lintersec, T_Seg[j]);
        ajouter_segment(&T_Seg[j]->Lintersec, T_Seg[i]);
        cpt++;
      }
    }
  }
  free(T_Seg);
  // return the number of intersections
  return cpt;
}
/*
int verifier_nbintersection(Netlist* nl){
  int nbseg = nbSeg
  Segment** T_Seg = tableau_segments(nl);
}*/


/*Fonction standard*/
void sauvgarder_intersections(Netlist* nl,char* nomfichier);
