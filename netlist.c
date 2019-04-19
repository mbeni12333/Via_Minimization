#include "netlist.h"

Netlist* netlist_globale;
SVGwriter img;

Netlist* initialize_netlist(int NbRes){
  Netlist* temp = (Netlist*)malloc(sizeof(Netlist));
  // s'il y a une erreur
  if(!temp){
    fprintf(stderr, "Erreur Allocation Netlist\n");
    return NULL;
  }
  // sinon on initilise
  temp->NbRes = NbRes;
  // on cree le tableau de reseax;
  Reseau** T_Res = (Reseau**)malloc(sizeof(Reseau*)*NbRes);
  // erreur
  if(!T_Res){
    // free
    fprintf(stderr, "Erreur Allocation T_Res\n");
    return NULL;
  }// sinon

  temp->T_Res = T_Res;
  // mettre case a NULL
  temp->xmin = temp->ymin = temp->xoffsef = temp->yoffset = 0;
  temp->nbSeg = 0;
  temp->nbPt = 0;
  return temp;
}

/*Cette fonction permet de lire un reseau*/
Netlist* read_net_from_file(char* file){
  // on commence par ouvrir le fichier
  FILE* f = fopen(file, "r");
  double xmin, ymin, xmax, ymax; // utile plus tard svg
  int nbSeg = 0; // utile
  int nbPt = 0;
  // si le fichier n'existe pas
  if(!f){
    fprintf(f, "Erreur d'ouverture fichier net\n");
    return NULL;
  }
  // sinon on parse dans le fichier

  // no commence par lire le nombre de reseaux
  int NbRes = GetEntier(f);

  // on cree le Netlist
  Netlist* netlist = initialize_netlist(NbRes);
  if(!netlist){
    return NULL;
  }
  // on lit NbRes reseaux
  int i;
  for(i=0; i<NbRes; i++){
    // numero res / nb pts / nb_segments
    int NumRes = GetEntier(f);
    int NbPt = GetEntier(f);
    int NbSeg = GetEntier(f);
    //nb total de seg
    nbSeg+=NbSeg;
    nbPt+=NbPt;
    // on cree le reseau et on l'ajoute au netlist
    Reseau* current_reseau = initilize_reseau(NumRes, NbPt, NbSeg);
    if(!current_reseau){
      return NULL;
    }
    netlist->T_Res[NumRes] = current_reseau;
    // on lit tout les points du reseau
    int j;
    for(j=0; j<NbPt; j++){
      // NumPt / x / y
      int NumPt = GetEntier(f);
      double x = GetEntier(f);
      double y = GetEntier(f);
      if(j!=0){
        xmin = xmin > x ? x:xmin;
        ymin = ymin > y ? y:ymin;
        xmax = xmax < x ? x:xmax;
        ymax = ymax < y ? y:ymax;
      }else{
        xmin = x;
        ymin = y;
        xmax = x;
        ymin = y;
      }
      // on cree le point et on l'ajoute au reseau
      Point* current_point = initialize_point(x, y, NumRes);
      if(!current_point){
        return NULL;
      }
      current_reseau->T_Pt[NumPt] = current_point;
    }
    Point** T_Pt = current_reseau->T_Pt;
    // et on lit tout les segments
    for(j=0; j<NbSeg; j++){
      // on lit les points du segment
      int p1 = GetEntier(f);
      int p2 = GetEntier(f);

      int HouV = T_Pt[p1]->x == T_Pt[p2]->x;
      // on cree le segment
      Segment* current_segment =  initialize_segment(NumRes , p1, p2, HouV);
      if(!current_segment){
        return NULL;
      }
      // on ajoute l'element au deux liste de p1 et p2
      ajouter_segment(&T_Pt[p1]->Lincid, current_segment);
      ajouter_segment(&T_Pt[p2]->Lincid, current_segment);
    }
  }
  netlist->xmin = xmin;
  netlist->ymin = ymin;
  netlist->xoffsef = xmax-xmin;
  netlist->yoffset = ymax-ymin;
  netlist->nbSeg = nbSeg;
  netlist->nbPt = nbPt;
  netlist_globale = netlist;
  return netlist;
}
/*Tableau des segments*/
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
Point** tableau_points(Netlist* nl){
  if(!nl){
    fprintf(stderr, "Erreur Netlsit Vide\n");
    return NULL;
  }
  int i;
  // allocation du tab
  Point** T_Pt = (Point**)malloc(sizeof(Point*)*nl->nbPt);
  if(!T_Pt){
    fprintf(stderr, "Erreur allocation tableau points\n");
    return NULL;
  }
  Point** temp = T_Pt;
  // aucune Erreur
  Reseau** T_Res = nl->T_Res;
  for(i=0; i<nl->NbRes;i++){
    memcpy(temp, T_Res[i]->T_Pt, T_Res[i]->NbPt*sizeof(Point*));
    temp += T_Res[i]->NbPt;
  }

  /*for(i=0; i<nl->nbPt; i++){
    afficher_point(T_Pt[i]);
  }*/
  return T_Pt;
}
int nbSeg(Netlist* nl){
  return nl->nbSeg;
}
/*Enregistrer netlist dans un fichier.net*/
void sauvegarder_netlsit(Netlist* nl){
  
}
/*Enregister les intersesction dans un fichier .init*/
void sauvegarder_intersections(Netlist* nl, char* nomFichier){
  
}
/*Charger les intersections*/
void charger_intersections(Netlist* nl, char* nomFichier){

}
/*Creation de copie*/
Netlist* copie_netlist(Netlist* nl){
  return NULL;
}
/*Afficher une netlist*/
void afficher_netlist(Netlist* nl){
  if(nl == NULL){
    fprintf(stderr, "Netlist Vide !");
    return;
  }
  // on affiche tout les reseau
  int i;

  printf("Affichage de Netlist (%d Reseaux) : \n", nl->NbRes);

  for(i=0; i<nl->NbRes; i++){
    // on affiche le reseau i (reste a savoir )
    SVGlineRandColor(&img);
    SVGgroup(&img);
    afficher_reseau(nl->T_Res[i]);
    SVGgroup_end(&img);
  }
  printf("Netlist BOX(%f %f %f %f)\n", nl->xmin, nl->ymin, nl->xoffsef, nl->yoffset);
  printf("Fin de l'affichage \n");
}
/*Visualisation Netlist*/
void visualiser_netlist(Netlist* nl, char* nomFichier){
  // tests null

  // on initilise un svgwriter
  SVGinit(&img, nomFichier, nl->xmin, nl->ymin, nl->xoffsef, nl->yoffset);
  /* test ligne
  SVGpoint(&svg, 10, 10);
  SVGpoint(&svg, 10, 400);
  SVGline(&svg, 10, 10, 10, 400);
  SVGpoint(&svg, -30, 30);
  SVGpoint(&svg, 2000, 30);
  SVGline(&svg, -30, 30, 2000, 30);*/
  afficher_netlist(nl);


  // on finalise le fichier
  SVGfinalize(&img);
  // on libere l'espace memoire
}







/*Cette fonction permet de sauvegarder un reseau*/
void sauvegarde_de_la_netlist(Netlist *nl, char* nom_fichier){
  if (nl == NULL){
    fprintf(stderr,"Netlist vide... \n");
    return;
  }
  // on commence par ouvrir le fichier
  FILE* f = fopen(nom_fichier, "w");
  int i,j,k;
  int nbRes = nl->NbRes;
  
  // test d'allocation
  if(!f){
    fprintf(stderr, "Erreur d'ouverture fichier net\n");
    return;
  }
  // sinon on parcours la netliste
  fprintf(f, "%d\n",nbRes);

  for (i = 0; i<nbRes;i++){
    
    fprintf(f, "%d ",i);
    fprintf(f, "%d ",nl->T_Res[i]->NbPt);
    fprintf(f, "%d \n",nl->T_Res[i]->NbSeg);
    for(j = 0;j<nl->T_Res[i]->NbPt;j++){
      printf("Res %d\n", i);
      fprintf(f, "\t%d ",j);
      fprintf(f, "%.f ",nl->T_Res[i]->T_Pt[j]->x);
      fprintf(f, "%.f \n",nl->T_Res[i]->T_Pt[j]->y);
    }
      for(j=0;j<nl->T_Res[i]->NbPt;j++){

        Point *tmp = nl->T_Res[i]->T_Pt[j];
        Cell_segment* current = tmp->Lincid;
        while(current){
          if(current->seg->printed == 0){
            fprintf(f, "\t%d ",current->seg->p1);
            fprintf(f, "%d \n",current->seg->p2);
            current->seg->printed =1;
          }
          current=current->suiv;
        }
        
      }
      for(j=0;j<nl->T_Res[i]->NbPt;j++){

        Point *tmp = nl->T_Res[i]->T_Pt[j];
        Cell_segment* current= tmp->Lincid;
        while(current){
          current->seg->printed = 0;
          current = current->suiv;
        }
    }
  }
}



void sauvegarde_intersection(Netlist* nl,char * nom_fichier){
  if(nl==NULL){
    fprintf(stderr,"Netlist vide !\n");
    return;
  }
  int i,j;
  int nbRes = nl->NbRes;
  FILE *f = fopen(nom_fichier,"w");
  if (f==NULL){
    fprintf(stderr,"Erreur lors de l'ouverture du fichier \n");
    return;
  }
  for (i = 0; i< nbRes; i++){
    for(j=0;j< nl->nbPt;j++){
        Cell_segment* L_seg = nl->T_Res[i]->T_Pt[j]->Lincid;
        while(L_seg){
          Segment* seg_current = L_seg->seg;
          Cell_segment* L_intersections = seg_current->Lintersec;
          while(L_intersections){

            if (L_intersections->seg->printed == 0){
              fprintf(f,"%d %d %d %d %d %d \n",seg_current->NumRes, seg_current->p1, seg_current->p2, L_intersections->seg->NumRes, L_intersections->seg->p1, L_intersections->seg->p2 );
            }
            L_intersections = L_intersections->suiv;
          }
          
      L_seg->seg->printed = 1;
      L_seg = L_seg->suiv;
    }

    }
  
  }


}