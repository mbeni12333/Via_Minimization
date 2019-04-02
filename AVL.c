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
    nouv->clef = n->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;

    return nouv;
}


//Rotation Droite 
void Rotation_droite(AVL **ab){
    
    AVL * r = *ab;
    AVL * g = (*ab)->fils_gauche;

    int poid_a = (*ab)->poid;
    int poid_b = (*ab)->fils_gauche->poid;

    r->fils_gauche = g->fils_droite;
    g->fils_droite = r;
    *ab = g;
    /*DEGUEUULLASSSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE !!!!!*/
    (*ab)->fils_gauche->poid = poid_a-max(poid_b,0)-1;
    (*ab)->poid = min(min(poid_a-2,poid_a+poid_b-2),min(poid_b-1,poid_a + poid_b-2));
}

//Rotation Gauche 
void Rotation_gauche(AVL **ab){

    AVL * b = (*ab)->fils_droite;
    int poid_a = (*ab)->poid;
    int poid_b = b->poid;
    //Rotation
    (*ab)->fils_gauche = b->fils_droite;
    b->fils_gauche = *ab;
    *ab = b;
    //Mise a jour des poids degueulasse
    (*ab)->fils_gauche->poid = poid_a-min(poid_b,0)+1;
    (*ab)->poid = max(max(poid_a+2 , poid_a+poid_b+2),max(poid_b+1,poid_a+poid_b+2));   

}
//Fonction d'equilibrage de l'arbre 
void equilibrer(AVL ** ab){
    /*Degueulasse*/

    if(!*ab)
        return;

    if ((*ab)->poid == 2){
        if!((*ab)->fils_droite)
            return;
        if ((*ab)->fils_droite->poid < 0)
            Rotation_droite(&((*ab)->fils_droite));   
        Rotation_gauche(ab);
    }    
    else if ((*ab)->poid == -2){
        if(!(*ab)->fils_gauche)
           return;
        if ((*ab)->fils_gauche->poid > 0)
            Rotation_gauche(&((*ab)->fils_gauche));    
        Rotation_droite(ab);
    }    

}

//Fonction d'ajout de segment a la structure
void Ajout_segment_AVL(AVL **ab, Segment* s , Netlist* n){
    int h = 0;
    if (!s || !n)return;
    // eviter d'utiliser les & en gardant une copie AVL* g = *ab
    if(*ab == NULL){
        *ab = Ajout_feuille(s,n);  
        return;  
    }
    if((*ab)->clef >= n->T_Res[s->NumRes]->T_Pt[s->p1]->y){
            Ajout_segment_AVL(&((*ab)->fils_gauche),s,n);
            h = -1 ;
    }else{
            Ajout_segment_AVL(&((*ab)->fils_droite),s,n);
            h = 1;  
    }
    (*ab)->poid = (*ab)->poid+h;
    //equilibrer(ab);

}
//suppression du minimum
void Suppression_segment_AVL(AVL **ab, Segment* s , Netlist* n){
    //int h = 1; NON
    AVL* tmp;
    if (!s || !n)return;
    
    if(*ab == NULL){
        printf("Aucun element a supprimer...");
        return;     
    } 

    double y = n->T_Res[s->NumRes]->T_Pt[s->p1]->y;

    if((*ab)->clef > y){
            Suppression_segment_AVL(&((*ab)->fils_gauche),s,n);
            h = -h ;
    }else if((*ab)->clef < y){
            Suppression_segment_AVL(&((*ab)->fils_droite),s,n);
    }else{

        // cas ou on a trouvé l'element

        /*ON S EN FOUUUUUUUU 
            if(((*ab)->fils_gauche == NULL) &&((*ab)->fils_gauche != NULL)){
                *ab = (*ab)->fils_droite;
                free_AVL((*ab)->fils_droite->fils_droite);
                h=-h;    
            }else if(((*ab)->fils_gauche != NULL) &&((*ab)->fils_gauche == NULL)){ 
                *ab = (*ab)->fils_gauche ;
                free_AVL((*ab)->fils_gauche->fils_gauche);
                h=-h;
            }    
            else if(((*ab)->fils_gauche == NULL) &&((*ab)->fils_gauche == NULL))    
                free_AVL(*ab);
            else{
                tmp = enleve_min((*ab)->fils_droite);
                tmp->fils_droite = (*ab)->fils_droite;
                tmp->fils_gauche = (*ab)->fils_gauche;

            } 
        */

    }
    //(*ab)->poid = (*ab)->poid+h;
    equilibrer(ab);

}
//recherche du minimum d'un arbre
AVL* enleve_min(AVL* ab){
    AVL * min;
    if(ab->fils_gauche == NULL){
        min = ab;
        //free_AVL(ab); WHY . WHYY .. JUST WHYYYYY 
    }else{
        enleve_min(ab->fils_gauche);
    }
    ab->poid = ab->poid-1;
    //equilibrer(&ab); WHYYYYYYYYYYY 
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
      
