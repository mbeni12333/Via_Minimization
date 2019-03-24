#include "AVL.h"

AVL* Ajout_feuille(Segment * seg, Netlist *n){
    AVL* nouv = (AVL*)malloc(sizeof(AVL));
    //on vérifie s'il n'y a pas d'erreur d'allocation 
    if nouv == NULL {
        fprintf(stderr, "Erreur Allocation AVL \n");
        return NULL;
    }
    nouv->seg = seg;
    nouv->fils_gauche = NULL;
    nouv->fils_droite = NULL; 
    nouv->hauteur = 1;
    nouv->clef = n->T_Res->T_Pt[seg->p1]->y;

    return nouv;
}

//Fonction d'ajout de segment a la structure
void Ajout_segment(AVL * ab, Segment* s , Netlist* n){
    if (s == NULL ||n == NULL)return;
    if(*ab == NULL){
        *ab = Ajout_feuille(s,n);     
    }
    else{
        if((*ab)->clef >= n->T_Res->T_Pt[s->p1]->y){
            Ajout_segment(&((*ab)->fils_gauche),s,n);
        }else{
            Ajout_segment(&((*ab)->fils_droite),s,n);
        }
        (*ab)->hauteur = 1+max(hauteur(&(*ab)->fils_gauche),hauteur(&(*ab)->fils_gauche));
        int hg = hauteur(&(*ab)->fils_gauche),hd = hauteur(&(*ab)->fils_droite);
        if(hg-hd == 2){
            if (hauteur(&(*ab)->fils_gauche->fils_gauche)) < hauteur(&(*ab)->fils_gauche->fils_droite)){
                Rotation_gauche(&(*ab)->fils_gauche);
            }
            Rotation_droite(ab); 
        }else{
            if(hg-hd == -2){
                if (hauteur(&(*ab)->fils_droite->fils_droite)) < hauteur(&(*ab)->fils_droite->fils_gauche)){
                    Rotation_droite(&(*ab)->fils_droite);
                }
                Rotation_gauche(ab);
            } 
        }
    }


}

//Fonction max 
int max(int a, int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
//Calcule de la hauteur d'un arbre/sous-arbre 
int hauteur(*AVL ab){
    if (ab == NULL){
        return 0;//Arbre vide 
    }
    return 1+max(hauteur(&(*ab)->fils_gauche), hauteur(&(*ab)->fils_droite));
}

//Rotation Droite 
void Rotation_droite(AVL *ab){
    AVL * r = *ab;
    AVL * g = (*ab)->fils_gauche;
    AVL * d = (*ab)->fils_droite;

    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;

    (*ab)->fils_gauche->hauteur = hauteur(&(*ab)->fils_gauche);
    (*ab)->hauteur = hauteur(ab);

}

//Rotation Gauche 
void Rotation_gauche(AVL *ab){
    AVL * g = *ab;
    AVL * r = (*ab)->fils_droite;
    AVL * d = r->fils_droite;
  
    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;
    
    (*ab)->fils_gauche->hauteur = hauteur(&(*ab)->fils_gauche);
    (*ab)->hauteur = hauteur(ab);

} 
//Libere l'espace alloue pour l'arbre AVL
void free_AVL(AVL *ab){
    if (ab->fils_gauche == NULL && ab->fils_droite == NULL && !ab){
        free ab->seg;
        free ab;
    }
    free_AVL(ab->fils_gauche);
    free_AVL(ab->fils_droite);
}