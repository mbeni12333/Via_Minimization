#include "AVL.h"


AVL* Ajout_feuille(Segment * seg, Netlist *n){
    AVL* nouv = (AVL*)malloc(sizeof(AVL));
    //on vérifie s'il n'y a pas d'erreur d'allocation 
    if (nouv == NULL) {
        fprintf(stderr, "Erreur Allocation AVL \n");
        return NULL;
    }
    if(seg->HouV != 0){
        printf("Ce segment n'est pas horizontal...");
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
    if (*ab == NULL)
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
    (*ab)->fils_droite->hauteur = 1+max(hauteur((*ab)->droite->fils_gauche),hauteur((*ab)->fils_droite->fils_droite));
    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));
}

//Rotation Gauche 
void Rotation_gauche(AVL **ab){

    AVL * b = (*ab)->fils_droite;
    //Rotation
    (*ab)->fils_droite = b->fils_gauche;
    b->fils_droite = *ab;
    *ab = b;
    //Mise a jour des poids  
    (*ab)->fils_gauche->hauteur = 1+max(hauteur((*ab)->fils_gauche->fils_gauche),hauteur((*ab)->fils_gauche->fils_droite));
    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite)); 

}

//Fonction qui donne la différence de hauteur 
int getDiff(AVL* ab){
    if(*ab==NULL) return 0;
    return hauteur((*ab)->fils_gauche) - hauteur((*ab)->fils_droite);
}
 

//Fonction d'ajout de segment a la structure
void Ajout_segment_AVL(AVL **ab, Segment* s , Netlist* n){
    int diff;
    if (!s || !n)return;
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
    diff = getDiff(ab);
    if (diff == 2){
        if(hauteur((*ab)->fils_gauche->fils_gauche)<hauteur((*ab)->fils_gauche->fils_droite)){
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
    AVL* tmp;
    if (!s || !n)return;
    
    if(*ab == NULL){
        printf("Aucun element a supprimer...");
        return;     
    } 

    double y = n->T_Res[s->NumRes]->T_Pt[s->p1]->y;

    if((*ab)->clef > y){
            Suppression_segment_AVL(&((*ab)->fils_gauche),s,n);
    }else if((*ab)->clef < y){
            Suppression_segment_AVL(&((*ab)->fils_droite),s,n);
    }else{
        if((*ab)->fils_gauche == NULL || (*ab)->fils_droite == NULL){
            AVL* tmp;
            if((*ab)->fils_gauche){
                tmp = (*ab)->fils_gauche;
            }else{
                tmp = (*ab)->fils_droite;
            }
            //Pas de fils 
            if (tmp == NULL){
                free(&ab);
            }
            else{// Cas à UN fils:
                *ab = tmp; // On recupere le fils et on écrase la racine
                free(tmp);
            }
        }else{//Cas avec deux fils
            //On recupere le minimum du sous arbre de droite
            AVL* tmp = recup_min((*ab)->fils_droite); 
            (*ab)->segment = tmp->segment; // On le remplace par le segment que l'on veut supprimer
            Suppression_segment_AVL(&(*ab)->fils_droite, tmp->segment, n); // On l'enleve de son emplacement precedent
        }        
    }
    if(*ab == NULL){
        return; //Cas ou il n'y a qu'un noeud dans l'arbre
    } 
    //Mise a jour de la hauteur
    (*ab)->hauteur = 1+max(hauteur((*ab)->fils_gauche),hauteur((*ab)->fils_droite));
    //Verification de l'equilibre de l'arbre
    diff = getDiff(*ab);
    if (diff == 2){
        if(hauteur((*ab)->fils_gauche->fils_gauche)<hauteur((*ab)->fils_gauche->fils_droite)){
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

//recherche du minimum d'un arbre
AVL* recup_min(AVL* ab){
    AVL * min;
    if(ab->fils_gauche == NULL){
        min = ab;
    }else{
        recup_min(ab->fils_gauche);
    }
    return min;
}



/*Affichage*/
void afficher_AVL(AVL* a){
    if(!a){
        return;
    }
    afficher_AVL(a->fils_gauche);
    printf("%f ", a->clef);
    afficher_AVL(a->fils_droite);
}





//Libere l'espace alloue pour l'arbre AVL
void free_AVL(AVL **ab){
    if(!*ab)return;                                                 
    // on libere recursivement
    free_AVL(*ab->fils_gauche);
    free_AVL(*ab->fils_droite);
    // on libere l'element
    free(*ab);
    *ab = NULL;

}
      
