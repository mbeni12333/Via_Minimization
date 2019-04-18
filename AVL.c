#include "AVL.h"


AVL* Ajout_feuille(Segment * seg, Netlist *n){
    AVL* nouv = (AVL*)malloc(sizeof(AVL));
    //on vérifie s'il n'y a pas d'erreur d'allocation
    if (nouv == NULL) {
        fprintf(stderr, "Erreur Allocation AVL \n");
        return NULL;
    }
    nouv->seg = seg;
    nouv->fils_gauche = NULL;
    nouv->fils_droite = NULL;
    nouv->hauteur = 1;
    nouv->clef = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

    return nouv;
}

//Donne la hauteur d'un arbre
int hauteur(AVL *ab){
    if (ab == NULL)
        return 0;
    return ab->hauteur;
}

//Rotation Droite
void Rotation_droite(AVL **ab){

    AVL * r = *ab;
    AVL * g = (*ab)->fils_gauche;

    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;
    /*DEGUEUULLASSSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE !!!!!*//*Corrigé normalement...*/
    (*ab)->fils_droite->hauteur = 1+max(hauteur((*ab)->fils_droite->fils_gauche),hauteur((*ab)->fils_droite->fils_droite));
    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));
}

//Rotation Gauche
void Rotation_gauche(AVL **ab){

    AVL * b = (*ab)->fils_droite;
    //Rotation
    (*ab)->fils_droite = b->fils_gauche;
    b->fils_gauche = *ab;
    *ab = b;
    //Mise a jour des poids
    (*ab)->fils_gauche->hauteur = 1+max(hauteur((*ab)->fils_gauche->fils_gauche),hauteur((*ab)->fils_gauche->fils_droite));
    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));

}

//Fonction qui donne la différence de hauteur
int getDiff(AVL* ab){
    if(ab==NULL) return 0;
    return hauteur(ab->fils_gauche) - hauteur(ab->fils_droite);
}


//Fonction d'ajout de segment a la structure
void Ajout_segment_AVL(AVL **ab, Segment* s , Netlist* n){
    int diff;
    if (!s || !n)return;
    if(s->HouV != 0){
        printf("Segment vertical");
        return;
    }
    // eviter d'utiliser les & en gardant une copie AVL* g = *ab
    if(*ab == NULL){
        *ab = Ajout_feuille(s,n);
        return;
    }
    if((*ab)->clef >= n->T_Res[s->NumRes]->T_Pt[s->p1]->y){

            Ajout_segment_AVL(&((*ab)->fils_gauche),s,n);

    }else{
            Ajout_segment_AVL(&((*ab)->fils_droite),s,n);

    }

    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));
    diff = getDiff(*ab);
    if (diff == 2){
        if(hauteur((*ab)->fils_gauche->fils_gauche) < hauteur((*ab)->fils_gauche->fils_droite)){
            Rotation_gauche(&(*ab)->fils_gauche);
        }
        Rotation_droite(ab);
    }else{
        if(diff == -2){
            if (hauteur((*ab)->fils_droite->fils_droite)< hauteur((*ab)->fils_droite->fils_gauche)){
                Rotation_droite(&(*ab)->fils_droite);
            }
            Rotation_gauche(ab);
        }
    }

}
//suppression d'un segment
void Suppression_segment_AVL(AVL **ab, Segment* s , Netlist* n){
    //int h = 1; NON
    int diff; // Oui :D
    if (!s || !n)return;

    if(*ab == NULL){
        //printf("Aucun element a supprimer...");
        return;
    }

    double y = n->T_Res[s->NumRes]->T_Pt[s->p1]->y;
    /*if(*ab == NULL)
      return; //Cas ou il n'y a qu'un noeud dans l'arbre*/
    if((*ab)->clef == y){
      if(!(*ab)->fils_gauche  || !(*ab)->fils_droite ){
          AVL* tmp = (*ab)->fils_gauche ? (*ab)->fils_gauche: (*ab)->fils_droite;
          /*if((*ab)->fils_gauche){
              tmp = (*ab)->fils_gauche;
          }else{
              tmp = (*ab)->fils_droite;
          }*/
          //Pas de fils

          free(*ab);
          *ab = tmp;
          return;
          /*
          if (tmp == NULL){
              free(*ab);
          }else{// Cas à UN fils:
            // Hoein '-'
              free(*ab);
              *ab = tmp; // On recupere le fils et on écrase la racine
              //free(tmp);
          }*/
      }
        //Cas avec deux fils
          //On recupere le minimum du sous arbre de droite
          AVL* pointeur_min = recup_min(&(*ab)->fils_droite);
          AVL* racine = *ab;
          if(!pointeur_min){
              printf("WTF MAN\n");
          }
          // on met le min dans la position de la racine
          pointeur_min->fils_gauche = racine->fils_gauche;
          pointeur_min->fils_droite = racine->fils_droite;

          // on pointe la racine vers la nouvelle racine
          *ab = pointeur_min;
          free(racine);
          printf("\nmin = %.f, ancien racine = %.f\n", pointeur_min->clef, racine->clef);
          return;
      }

    (*ab)->clef > y ? Suppression_segment_AVL(&((*ab)->fils_gauche),s,n):
                      Suppression_segment_AVL(&((*ab)->fils_droite),s,n);
    /*
    if((*ab)->clef > y){
          Suppression_segment_AVL(&((*ab)->fils_gauche),s,n);
    }else
          Suppression_segment_AVL(&((*ab)->fils_droite),s,n);
    */

    //Verification de l'equilibre de l'arbre
    diff = getDiff(*ab);
    if (diff == 2){
        if(hauteur((*ab)->fils_gauche->fils_gauche) < hauteur((*ab)->fils_gauche->fils_droite)){
            Rotation_gauche(&(*ab)->fils_gauche);
        }
        Rotation_droite(ab);
    }else if(diff == -2){
        if (hauteur((*ab)->fils_droite->fils_droite) < hauteur((*ab)->fils_droite->fils_gauche)){
            Rotation_droite(&(*ab)->fils_droite);
        }
        Rotation_gauche(ab);
    }
    //Mise a jour de la hauteur, inutile
    //(*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));
}
//recherche du minimum d'un arbre
AVL* recup_min(AVL** ab){

    AVL * min;
    if(*ab == NULL)
        return NULL;
    if((*ab)->fils_gauche == NULL){
        min = *ab;
        *ab = (*ab)->fils_droite;
        // deconnecter min
        min->fils_droite = NULL;
        min->fils_gauche = NULL;
        return min;
    }
    
    AVL* tmp = recup_min(&(*ab)->fils_gauche);
    if(!tmp){
        printf("WTFFFFUUFFFF '-' \n");
    }
    int diff = getDiff(*ab);


    // equilibrer
    if (diff == 2){
        if(hauteur((*ab)->fils_gauche->fils_gauche) < hauteur((*ab)->fils_gauche->fils_droite)){
            Rotation_gauche(&(*ab)->fils_gauche);
        }
        Rotation_droite(ab);
    }else if(diff == -2){
        if (hauteur((*ab)->fils_droite->fils_droite) < hauteur((*ab)->fils_droite->fils_gauche)){
            Rotation_droite(&(*ab)->fils_droite);
        }
        Rotation_gauche(ab);
    }
    //(*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));, inutile
    // mise a jour des hauteurs
    return  tmp;

}



/*Affichage*/
void afficher_AVL(AVL* a){
    if(!a){
        return;
    }
    
    afficher_AVL(a->fils_gauche);
    printf("%.f ", a->clef);
    afficher_AVL(a->fils_droite);
}





//Libere l'espace alloue pour l'arbre AVL
void free_AVL(AVL **ab){
    if(!*ab)return;
    // on libere recursivement
    free_AVL(&(*ab)->fils_gauche);
    free_AVL(&(*ab)->fils_droite);
    // on libere l'element
    free(*ab);
    *ab = NULL;

}
AVL* prem_segment_avl(AVL* a, double y1, double y2){
    return NULL;   
}
Cell_segment* avl2list(AVL* a){
    return NULL;
}