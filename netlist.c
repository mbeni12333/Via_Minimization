#include "netlist.h"

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
  return temp;
}

/*Cette fonction permet de lire un reseau*/
Netlist* read_net_from_file(char* file){
  // on commence par ouvrir le fichier
  FILE* f = fopen(file, "r");

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


    // on cree le reseau et on l'ajoute au netlist
    Reseau* current_reseau = initilize_reseau(NumRes, NbPt);
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
  return netlist;
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
    afficher_reseau(nl->T_Res[i]);
  }
  printf("Fin de l'affichage \n");
}
/*Visualisation Netlist*/
void visualiser_netlist(Netlist* nl, char* nomFichier){
  // tests null

  // on initilise un svgwriter
  SVGwriter svg;
  SVGinit(&img, nomFichier, 1000, 4000);
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