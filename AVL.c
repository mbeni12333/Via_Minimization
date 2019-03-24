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
    nouv->clef = n->T_Res->T_Pt[seg->p1]->y;

    return nouv;
}

//Fonction d'ajout de segment a la structure
void Ajout_segment(AVL **ab, Segment* s , Netlist* n){
    if (s == NULL ||n == NULL)return;
    // eviter d'utiliser les & en gardant une copie AVL* g = *ab
    if(*ab == NULL){
        *ab = Ajout_feuille(s,n);     
    }
    else{
        
        if((*ab)->clef >= n->T_Res->T_Pt[s->p1]->y){
            Ajout_segment(&((*ab)->fils_gauche),s,n);
        }else{
            Ajout_segment(&((*ab)->fils_droite),s,n);
        }
        // pourquoi ne pas utiliser la fonction, elle fait exactement ça
        // aussi hauteur prend un pointeur simple on a pas besoin des &
        (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_gauche));
        // hauteur en o(n), on peut acceder directement par la structure
        int hg = hauteur((*ab)->fils_gauche),hd = hauteur((*ab)->fils_droite);
        // il serais preferable de voir la difference > 1 que de voir == 2, il se peut qu'un arbre ai un fils +2 qu'un autre
        // meme si ce cas est peu probable c'est plus propre
        // tu ne verifie pas si un valeur est null, et on risque le segmentation fault
        if(hg-hd == 2){
            // o(n)
            if (hauteur((*ab)->fils_gauche->fils_gauche)) < hauteur((*ab)->fils_gauche->fils_droite)){
                Rotation_gauche((*ab)->fils_gauche);
            }
            Rotation_droite(ab); 
        }else{
            if(hg-hd == -2){
                if (hauteur((*ab)->fils_droite->fils_droite)) < hauteur((*ab)->fils_droite->fils_gauche)){
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
int hauteur(AVL *ab){
    if (ab == NULL){
        return 0;//Arbre vide 
    }
    // ce n'est pas la peine d'utiliser des & et *
    return 1 + max(hauteur(ab->fils_gauche), hauteur(ab->fils_droite));
}

//Rotation Droite 
void Rotation_droite(AVL **ab){
    // double etoile car on risque de changer la racine
    AVL * r = *ab;
    AVL * g = (*ab)->fils_gauche;
    AVL * d = (*ab)->fils_droite;

    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;
    // calcul hauteur en o(n) 
    (*ab)->fils_gauche->hauteur = hauteur(&(*ab)->fils_gauche);
    (*ab)->hauteur = hauteur(ab);

}

//Rotation Gauche 
void Rotation_gauche(AVL **ab){
    /*Fonction a revoir*/
    // on risque de changer la racine donc on donne une etoile de plus a ab
    // cette fonction
    AVL * g = *ab;

    AVL * r = (*ab)->fils_droite;
    // on sait pas si r != NULL risque de segmentation fault
    AVL * d = r->fils_droite;
    // g->fils droite EST r, tu pointe r->fils_gauce vers lui meme (boucle)
    r->fils_gauche = g->fils_droite;
    // g->fils_droite EST r 
    g->fils_droite = r;
    // g EST *ab
    *ab = g;
    
    (*ab)->fils_gauche->hauteur = hauteur(&(*ab)->fils_gauche);
    // on calcule la hauteur pour rien, c'est en o(N) alors qu'on peut acceder directement 
    // a la hauteur a partir de la structure (*ab)->fils_droite->hauteur en o(1)
    (*ab)->hauteur = hauteur(ab);

} 
//Libere l'espace alloue pour l'arbre AVL
void free_AVL(AVL *ab){
    // cas de base simplifié
    if(!ab)return;
    // on libere recursivement
    free_AVL(ab->fils_gauche);
    free_AVL(ab->fils_droite);
    // on libere l'element
    // on libere pas le segment
    free(ab);
}
