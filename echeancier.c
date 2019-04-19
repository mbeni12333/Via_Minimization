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
        if(!seg->HouV){
            if(p1->x > p2->x){
                /*degueulasse*/
                E = init_elem_echeancier(init_extremite(p1->x, 2,seg, seg->p1));
                E->suiv = init_elem_echeancier(init_extremite(p2->x, 1,seg, seg->p2));
            }else{
                E = init_elem_echeancier(init_extremite(p2->x, 2, seg, seg->p2));
                E->suiv = init_elem_echeancier(init_extremite(p1->x, 1,seg, seg->p1));
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
                return -1;
            }else{
                return 1;
            }
        }else if(extb->VouGouD == 0){
            if(exta->VouGouD == 1){
                return 1;
            }else{
                return -1;
            }
        }else{
            //printf("It actually happened, 2 ext same x not vertical\n");
            //printf("x1 = %.f x2 = %.f v1 = %d v2 = %d\n", exta->x, extb->x, exta->VouGouD, extb->VouGouD);
            //afficher_segment(exta->seg);
            //printf(" and ");
            //afficher_segment(exta->seg);
            if(exta->VouGouD < extb->VouGouD)
              return 1;
            else if(exta->VouGouD > extb->VouGouD)
              return -1;
            else return 0;
            ;
        }
    }
}
Echeancier *mergeUtil(Echeancier *h1, Echeancier *h2){
    // if only one node in first list
    // simply point its head to second list

    if (!h1->suiv){

        h1->suiv = h2;
        return h1;
    }

    // Initialize current and next pointers of
    // both lists
    Echeancier *curr1 = h1, *next1 = h1->suiv;
    Echeancier *curr2 = h2, *next2 = h2;

    while (next1 && next2){
        // if curr2 lies in between curr1 and next1
        // then do curr1->curr2->next1
        int cond1 = compare_extremite(curr1->ext, curr2->ext);
        int cond2 = compare_extremite(curr2->ext, next1->ext);

        if (cond1 != -1 && cond2 != -1){

            next2 = curr2->suiv;
            curr1->suiv = curr2;
            curr2->suiv = next1;

            // now let curr1 and curr2 to point
            // to their immediate next pointers
            curr1 = curr2;
            curr2 = next2;
        }else{
            // if more nodes in first list
            if (next1->suiv){

                next1 = next1->suiv;
                curr1 = curr1->suiv;
            }

            // else point the last node of first list
            // to the remaining nodes of second list
            else{

                next1->suiv = curr2;
                return h1;
            }
        }
    }


    /*while(next1 && next2){
      int cond1 = compare_extremite(next2, next1);

      while(cond1 == 0 || cond1 == 1){
        next2 = next2->suiv;
        cond1 = compare_extremite(next2, next1);
      }
      if(!next2->suiv){

        curr1->suiv = curr2;
        next2->suiv = next1;

        return h1;
      }

      curr1 = next1;
      curr2 = next2;

      next1 = curr1->suiv;
      next2 = curr2->suiv;
    }
    if(next1){

    }
    if(next2){

    }*/
    return h1;
}

// Merges two given lists in-place. This function
// mainly compares head nodes and calls mergeUtil()
Echeancier *merge(Echeancier *h1, Echeancier *h2){

    if (!h1)
        return h2;
    if (!h2)
        return h1;

    // start with the linked list
    // whose head data is the least
    if (compare_extremite(h1->ext,h2->ext) == 1)
        return mergeUtil(h1, h2);
    else
        return mergeUtil(h2, h1);
}
/*Echeancier* merge(Echeancier* a, Echeancier* b){
    Merge de deux listes trié
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
}*/
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
    //afficher_echeancier(E);
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
            printf("%.f(%d) ->", current->ext->x, current->ext->VouGouD);
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
    //afficher_echeancier(E);
    // T est une liste
    Cell_segment* cell_seg = NULL;
    //Cell_segment* tail = NULL;
    Echeancier* current_echeancier = E;
    Extremite* ext;

    //printf("%d ", cpt);
    int i = 0;
    for(i=0; i<=cpt; i++){
        // pour chaque Extremite
        ext = current_echeancier->ext;
        //printf("Current extremite VouGouD = %d NumRes = %d y = ", ext->VouGouD, ext->seg->NumRes);
        //afficher_segment(current_echeancier->ext->seg);
        //printf("\n");
        //printf("%.f ", ext->x);
        //afficher_cell_segment(cell_seg);
        switch(ext->VouGouD){
            case 1: ;/*printf("Ajout !\n")*/; ajouter_segment_trie(nl, &cell_seg, ext->seg);
                     //tail = cell_seg;
                /*}else{
                    //ajouter_segment(&tail->suiv, ext->seg);
                    //tail = tail->suiv;
                }*/
                break;
            case 2: ;/*printf("Suppression !")*/;supprime_segment(&cell_seg, ext->seg);
                break;
            case 0:; Segment* v = ext->seg;
                     Reseau* r = nl->T_Res[v->NumRes];
                     Point * p1 = r->T_Pt[v->p1],
                           * p2 = r->T_Pt[v->p2];
                    //printf("x1=%.f y1=%.f x2=%.f y2=%.f\n", p1->x, p1->y, p2->x, p2->y);
                    // les y du seg vertical
                    double y1,y2;
                    y1 = min(p1->y, p2->y);
                    y2 = max(p1->y, p2->y);
                    //printf("Liste actuelle: (y1 = %.f y2= %.f)\n", y1, y2);
                    //afficher_cell_segment(cell_seg);
                    //printf("\n");
                    Cell_segment* cell_h = prem_segment_apres(nl, cell_seg, y1);
                    if(cell_h != NULL){
                        Segment* h = cell_h->seg;
                        while(cell_h && nl->T_Res[h->NumRes]->T_Pt[h->p1]->y <= y2){
                            //printf("HEY intersect ? \n");
                            if(h->NumRes != v->NumRes){
                                //printf("OUI : ");
                                //afficher_segment(h);
                                //printf("\n");
                                ajouter_segment(&v->Lintersec, h);
                                ajouter_segment(&h->Lintersec, v);
                                cpt_intersect++;
                            }
                            cell_h = AuDessus(nl, cell_h, y2);
                            if(cell_h != NULL)
                                h = cell_h->seg;
                        }
                    }else{
                        //printf("C'est pour caaa !!! ");
                    }
                break;
            default:
                fprintf(stderr, "EREUUUUUUUUUUURRRR !!! \n");
                return 0;
        }
        // on incremente le pointeur de l'echeancier
        current_echeancier = current_echeancier->suiv;

    }
/*if(cell_seg){
    printf("NON VIIIIDE ");
    afficher_segment(cell_seg->seg);
    printf("\n");
}*/
//afficher_echeancier(E);
return cpt_intersect;
}
/*Fonction recursif qui permet de verifier intersection dans tout le sous arbre
  du plus petit au plus grand
*/
void helper_avl_intersecter(AVL* head, Segment* v, int* compteur, double y1, double y2){
  // cas de base
  if(!head){
    return;
  }
  //printf("Hy i exist\n");
  // fils fauche
  if(head->clef >= y1)
  helper_avl_intersecter(head->fils_gauche, v, compteur, y1, y2);
  //traitement necessaire
  // le segment actuelle n'est pas du meme reseau que v
  if((head->seg->NumRes != v->NumRes) && head->clef >= y1 && head->clef <= y2){
    // on ajoute les intersection
      ajouter_segment(&v->Lintersec, head->seg);
      ajouter_segment(&(head->seg)->Lintersec, v);
      // on incremente le compteur d'intetrsection
      *compteur = *compteur + 1;
  }
  // fils droite
  if(head->clef <= y2)
  helper_avl_intersecter(head->fils_droite, v, compteur, y1, y2);
}
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
        //printf("\ntout marche bien \n");
        //afficher_AVL(cell_seg);
        switch(ext->VouGouD){
            case 1: ;Ajout_segment_AVL(&cell_seg, ext->seg, nl);
                break;

            case 2: ;Suppression_segment_AVL(&cell_seg, ext->seg, nl, nl->T_Res[ext->seg->NumRes]->T_Pt[ext->seg->p1]->y);//printf("Hey i'm deleting\n");
                break;
            case 0:; Segment* v = ext->seg;
                     Reseau* r = nl->T_Res[v->NumRes];
                     Point * p1 = r->T_Pt[v->p1],
                           * p2 = r->T_Pt[v->p2];

                    // les y du seg vertical
                    int y1 = min(p1->y, p2->y),
                        y2 = max(p1->y, p2->y);

                    AVL* avl_h = prem_segment_avl(cell_seg, y1, y2); // a faire en minirecursif
                    //afficher_AVL(avl_h);
                    //printf("\n");
                    //printf("y min = %d, ymax = %d\n", y1, y2);
                    // appel recursif sur ce sous arbre et execution
                    helper_avl_intersecter(avl_h, v, &cpt_intersect, y1, y2);
                    /*Cell_segment* cell_h = avl2list(avl_h);
                    Cell_segment* current = cell_h;*/
                    // tant que la liste n'est pas vide
                    /* while(current){
                            if(cell_h->seg->NumRes != v->NumRes){
                                ajouter_segment(&v->Lintersec, current->seg);
                                ajouter_segment(&(current->seg)->Lintersec, v);
                                cpt_intersect++;
                            }
                            //h = AuDessus(nl, cell_h, y2);
                            current = current->suiv;
                    }*/
                        // faut liberer espace liste

                break;
            default:
                fprintf(stderr, "EREUUUUUUUUUUURRRR !!! \n");
                return 0;
        }
        // librer_avl

        // on incremente le pointeur de l'echeancier
        current_echeancier = current_echeancier->suiv;
    }

return cpt_intersect;
}
