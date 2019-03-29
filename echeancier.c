#include "echeancier.h"
/*Fonction d'initialisation d'une cellule*/
Extremite* init_extremite(double x, int VouGouD, Segment* seg, int NumPt){
    /*Crere un une extremite*/
    Extremite* ext = (Extremite*)malloc(sizeof(Extremite));
    if(!ext){
        fprintf(stderr, "Erreur d'allocation d'Extremite\n");
        return NULL;
    }else{
        /*Initilisation*/
        ext->x = x;
        ext->VouGouD = VouGouD;
        ext->seg = seg;
        ext->NumPt = NumPt;
        
        return ext;
    }
}
/**/
Echeancier* init_elem_echeancier(Extremite* ext){
    if(!ext){
        return NULL;
    }
    Echeancier* elem = (Echeancier*)malloc(sizeof(Echeancier));
    if(!elem){
        fprintf(stderr, "Erreur d'allocation d'echeancier\n");
        return NULL;
    }
    elem->ext = ext;
    elem->suiv = NULL;
    /*On retourne l'elem*/
    return elem;
}
Echeancier* ajouter_segment_echeancier(Netlist* nl, Segment* seg){
    /*On cree deux version du segment version extremite droite et gauche, si il est vertical on retourne une seul version*/

    if(!seg){
        fprintf(stderr, "Erreur segment Vide\n");
        return NULL;
    }else{
     Echeancier* E;
     Reseau* r1 = nl->T_Res[seg->NumRes];
     Point * p1 = r1->T_Pt[seg->p1],
           * p2 = r1->T_Pt[seg->p2];
        if(seg->HouV){
            if(p1->x > p2->x){
                /*degueulasse*/
                E = init_elem_echeancier(init_extremite(p1->x, 1,seg, seg->p1));
                E->suiv = init_elem_echeancier(init_extremite(p2->x, 2,seg, seg->p2));
            }else{
                E = init_elem_echeancier(init_extremite(p2->x, 1, seg, seg->p2));
                E->suiv = init_elem_echeancier(init_extremite(p1->x, 2,seg, seg->p1));
            }
        }else{
            E = init_elem_echeancier(init_extremite(p1->x, 0,seg,seg->p1));
        }

        return E;
    }
}
void split_liste(Echeancier* E, Echeancier** a, Echeancier** b){
    /*divise une liste en deux*/
    if(!E){
        return;
    }

    Echeancier* lent = E;
    Echeancier* rapide = E->suiv;;

    // on deplace rapide par deux  et lent par 1
    while(rapide != NULL){
        rapide = rapide->suiv;

        if(rapide != NULL){
            lent = lent->suiv;
            rapide = rapide->suiv;
        }
    }

    *a = E;
    *b = lent->suiv;
    lent->suiv = NULL;
}
int compare_extremite(Extremite* exta, Extremite* extb){
    if(!exta || !extb) return 0;
    if(exta->x < extb->x){
        return 1;
    }else if (exta->x > extb->x){
        return -1;
    }else{
        if(exta->VouGouD == 0){
            if(extb->VouGouD == 1){
                return 1;
            }else{
                return -1;
            }
        }else if(extb->VouGouD == 0){
            if(exta->VouGouD == 1){
                return -1;
            }else{
                return 1;
            }
        }
    }
}
Echeancier* merge(Echeancier* a, Echeancier* b){
    /*Merge de deux listes trié*/
    Echeancier* head;
    // cas de base
    if(!a){
        return b;
    }else if(!b){
        return a;
    }        

    // cas generale
    if(compare_extremite(a->ext, b->ext) == 1){
        head = a;
        head->suiv = merge(b, a->suiv);
    }else{
        head = b;
        head->suiv = merge(b->suiv, a);
    }

    return head;
}
void merge_sort(Echeancier** E){
    /*Tri en n log n*/
    if(*E == NULL || (*E)->suiv == NULL){
        return;
    }
    Echeancier *a, *b;
    split_liste(*E, &a, &b);
    // recursive
    merge_sort(&a);
    merge_sort(&b);
    // merge

    *E = merge(a, b);
    return;
}
/*Fonction creation netlist*/
Echeancier* creer_echeancier(Netlist* nl, int *cpt){
    /*Variables*/
    Echeancier* E; // pointe vers la tete
    Echeancier* tail; // pointe vers la fin
    /*On remplit d'abords un tableau de segments*/
    Segment** T = tableau_segments(nl);
    if(!T){
        fprintf(stderr, "Erreur Tableau segments vide\n");
        return NULL;
    }
    /*Pour chaque segment on ajoute en fin de liste le resultat de ajouter_segment*/
    int i = 0;
    E = ajouter_segment_echeancier(nl, T[0]);
    tail = E;
    for(i=1; i<nl->nbSeg; i++){

        while(tail->suiv != NULL){
            tail=tail->suiv;
            (*cpt)++;
            //printf("i = %d\n", i);
        }

        tail->suiv = ajouter_segment_echeancier(nl, T[i]);
        if(!tail->suiv){
            fprintf(stderr, "Erreur tail vide\n");
            free_echeancier(E);
            return NULL;
        }
    }
    while(tail->suiv != NULL){tail=tail->suiv;(*cpt)++;}
    /*On a plus besoin de T*/
    free(T);
    /*On tri l'echeancier*/

    merge_sort(&E);
    
    /*Finallement on le retourne*/
    return E;
}
/*Liberer Echeancier*/
void free_echeancier(Echeancier* E){
    if(!E){
        return;
    }
    free_echeancier(E->suiv);
    free(E->ext);// libere extremite
    free(E);
}
/*Affichage*/
void afficher_echeancier(Echeancier* E){
    if(!E){
        fprintf(stderr, "Echeancier vide\n");
        return;
    }else{
        Echeancier* current = E;
        printf("Affichage de l'echeancier (ordre croissant attendu\n");
        while(current){
            printf("%.f ", current->ext->x);
            current = current->suiv;
        }
        printf("\nFin de l'affichage\n");
    }
}



int intersect_baleyage(Netlist* nl){
    // cree l'echeancier
    int cpt = 0;
    int cpt_intersect = 0;
    Echeancier* E = creer_echeancier(nl, &cpt);
    // T est une liste
    Cell_segment* cell_seg = NULL;
    Echeancier* current_echeancier = E;
    Extremite* ext;
    
    //printf("CPT = %d\n", cpt);
    int i = 0;
    for(i=0; i<cpt; i++){
        // pour chaque Extremite
        ext = current_echeancier->ext;

        switch(ext->VouGouD){
            case 1: ;ajouter_segment_trie(nl, &cell_seg, ext->seg);
                break;
            case 2: ;supprime_segment(&cell_seg, ext->seg);
                break;
            case 0:; Segment* v = ext->seg;
                     Reseau* r = nl->T_Res[v->NumRes];
                     Point * p1 = r->T_Pt[v->p1],
                           * p2 = r->T_Pt[v->p2];

                    // les y du seg vertical
                    int y1 = min(p1->y, p2->y),
                        y2 = max(p1->y, p2->y);
                    
                    Cell_segment* cell_h = prem_segment_apres(nl, cell_seg, y1); 
                    if(cell_h != NULL){                   
                        Segment* h = cell_h->seg;
                        while(!h && nl->T_Res[h->NumRes]->T_Pt[h->p1]->y <= y2){
                            if(h->NumRes != v->NumRes){
                                ajouter_segment(&v->Lintersec, h);
                                ajouter_segment(&h->Lintersec, v);
                                cpt_intersect++;
                            }
                            h = AuDessus(nl, cell_h, y2);
                        }
                    }
                break;
            default:
                fprintf(stderr, "EREUUUUUUUUUUURRRR !!! \n");
                return 0;
        }
        // on incremente le pointeur de l'echeancier
        current_echeancier = current_echeancier->suiv;
    }

return cpt_intersect;
}
/*
int intersect_baleyage_avl(Netlist* nl){
    // cree l'echeancier
    int cpt = 0;
    int cpt_intersect = 0;
    Echeancier* E = creer_echeancier(nl, &cpt);
    // T est une liste
    AVL* cell_seg = NULL;
    Echeancier* current_echeancier = E;
    Extremite* ext;
    
    //printf("CPT = %d\n", cpt);
    int i = 0;
    for(i=0; i<cpt; i++){
        // pour chaque Extremite
        ext = current_echeancier->ext;

        switch(ext->VouGouD){
            case 1: ;Ajout_segment_AVL(&cell_seg, ext->seg, nl);
                break;
            case 2: ;supprime_segment(&cell_seg, ext->seg, nl);
                break;
            case 0:; Segment* v = ext->seg;
                     Reseau* r = nl->T_Res[v->NumRes];
                     Point * p1 = r->T_Pt[v->p1],
                           * p2 = r->T_Pt[v->p2];

                    // les y du seg vertical
                    int y1 = min(p1->y, p2->y),
                        y2 = max(p1->y, p2->y);
                    
                    Cell_segment* cell_h = prem_segment_apres(nl, cell_seg, y1); 
                    if(cell_h != NULL){                   
                        Segment* h = cell_h->seg;
                        while(!h && nl->T_Res[h->NumRes]->T_Pt[h->p1]->y <= y2){
                            if(h->NumRes != v->NumRes){
                                ajouter_segment(&v->Lintersec, h);
                                ajouter_segment(&h->Lintersec, v);
                                cpt_intersect++;
                            }
                            h = AuDessus(nl, cell_h, y2);
                        }
                    }
                break;
            default:
                fprintf(stderr, "EREUUUUUUUUUUURRRR !!! \n");
                return 0;
        }
        // on incremente le pointeur de l'echeancier
        current_echeancier = current_echeancier->suiv;
    }

return cpt_intersect;
}*/