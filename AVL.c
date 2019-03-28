
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
    nouv->poid = 0;
    nouv->clef = n->T_Res->T_Pt[seg->p1]->y;

    return nouv;
}



//Fonction max 
int max(int a, int b){
    if(a>=b){
        return a;
    }else{
        return b;
    }
}
//Fonction min
int min(int a, int b){
    if(a<=b){
        return a;
    }else{
        return b;
    }
}

//Rotation Droite 
void Rotation_droite(AVL **ab){
    
    AVL * r = *ab;
    AVL * g = (*ab)->fils_gauche;
    AVL * d = (*ab)->fils_droite;

    int poid_a = ab->poid;
    int poid_b = ab->fils_gauche->poid;

    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;
    ab->fils_gauche->poid = poid_a-max(poid_b,0)-1;
    ab->poid = min(min(poid_a-2,a+b-2),min(poid_b-1,poid_a + poid_b-2));
}

//Rotation Gauche 
void Rotation_gauche(AVL **ab){

    AVL * b = *ab->fils_droite;
    int poid_a = ab->poid;
    int poid_b = b->poid;
    //Rotation
    ab->fils_gauche = b->fils_droite;
    b->fils_gauche = ab;
    *ab = b;
    //Mise a jour des poids
    ab->fils_gauche->poid = poid_a-min(poid_b,0)+1;
    ->bal = max(max(poid_a+2,poid_a + poid_b+2),max(poid_b+1,poid_a+poid_b+2));   

}
//Fonction d'equilibrage de l'arbre 
void equilibrer(AVL * ab){
    if (ab->poid == 2){
        if (ab->fils_droite->poid < 0)
            Rotation_droite(&(*ab)->fils_droite);   
        Rotation_gauche(ab);
    }    
    else if (ab->poid == -2){
        if (ab->fils_gauche->poid > 0)
            Rotation_gauche(&(*ab)->fils_gauche);    
        Rotation_droite(ab);
    }    

}

//Fonction d'ajout de segment a la structure
void Ajout_segment(AVL **ab, Segment* s , Netlist* n){
    int h = 1;
    if (s == NULL ||n == NULL)return;
    // eviter d'utiliser les & en gardant une copie AVL* g = *ab
    if(*ab == NULL){
        *ab = Ajout_feuille(s,n);     
    }
    else{
        
        if(ab->clef >= n->T_Res->T_Pt[s->p1]->y){
            Ajout_segment(&((*ab)->fils_gauche),s,n);
            h = -h ;
        }else{
            Ajout_segment(&((*ab)->fils_droite),s,n);
        }  
    }
    ab->poid = ab->poid+h;
    equilibrer(ab);

}
//suppression du minimum
void Suppression_segment(AVL **ab, Segment* s , Netlist* n){
    int h = 1;
    AVL* tmp;
    if (s == NULL ||n == NULL)return;
    
    if(*ab == NULL){
        printf("Aucun element a supprimer...");
        return;     
    } 
    if(ab->clef > n->T_Res->T_Pt[s->p1]->y){
            Suppression_segment(&((*ab)->fils_gauche),s,n);
            h = -h ;
    }else if(ab->clef < n->T_Res->T_Pt[s->p1]->y){
            Suppression_segment(&((*ab)->fils_droite),s,n);
    }   else{
            if((ab->fils_gauche == NULL) &&(ab->fils_gauche != NULL)){
                ab = ab->fils_droite;
                free(&(*ab)->fils_droite->fils_droite);
                h=-h;    
            }else if((ab->fils_gauche != NULL) &&(ab->fils_gauche == NULL)) 
                ab = ab->fils_gauche ;
                free(&(*ab)->fils_gauche->fils_gauche);
                h=-h;
            else if((ab->fils_gauche == NULL) &&(ab->fils_gauche == NULL))    
                free(ab);
            else{
                tmp = enleve_min(ab->fils_droite);
                tmp->fils_droite = ab->fils_droite;
                tmp->fils_gauche = ab->fils_gauche;

            } 
    }
    ab->poid = ab->poid+h;
    equilibrer(ab);

}
//recherche du minimum d'un arbre
AVL* enleve_min(AVL* ab){
    AVL * min;
    if(ab->fils_gauche == NULL){
        min = ab;
        free(ab);
    }else{
        enleve_min(ab->fils_gauche);
    }
    ab->poid = ab->poid-1;
    equilibrer(ab);
    return min;
}

//Libere l'espace alloue pour l'arbre AVL
void free_AVL(AVL *ab){
    if(!ab)return;                                                 
    // on libere recursivement
    free_AVL(ab->fils_gauche);
    free_AVL(ab->fils_droite);
    // on libere l'element
    free(ab);
}
      