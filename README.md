# Via_Minimization
Projet d'Algorithmique 2I006
# DERNIER DELAIS LUNDI 26/03/2019
```
typedef Struct AVL{
  Segment* seg;
  int poid_gauche;
  int poid_droite;
  AVL* fils_gauche;
  AVL* fils_droite;
}AVL;
```
implementation de la structure d'AVL pour ameliorer la complexité de la fonction de balayage

# Usage
```
  ./tests_elemntaires fichier
  ./VisuNetlist <NomFichier.net> <nomFichier.html>
```

# Convention de collaboration

"Le nom des commits , quand crérer des branche, et quand merger"

type de changement + objet

Description du probleme + description solutoin
+ comment continuer

## ToDO list
- [X] structure AVL
- [X] Fonction d'ajout
- [ ] Fonction de suppression
- [X] Fonction rotation droite
- [X] Fonction rotation gauche
- [X] Fonction liberation memoire
- [ ] Fichier de tests validité
- [ ] Fichier de tests, graph de complexité


## Ressources
<a href="http://igm.univ-mlv.fr/~mac/ENS/DOC/arbravl_7.pdf">Explication de AVL</a>
