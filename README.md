# Via_Minimization
Projet d'Algorithmique 2I006

# Description

On appelle probleeme de conception de circuits VLSI (VLSI design problem, en anglais) l’ensemble du processus qui permet de positionner le circuit VLSI a sur un support, en prenant en compte toutes les caract ́eristiques de la technologie choisie concernant les composants et les r ́eseaux.

Le probleme de conception de circuits VLSI se d ́ecoupe traditionnellement en plusieurs ́etapes. En
effet, ce processus est tres complexe et il serait difficile de tout concevoir en une seule ́etape. De plus,
cette division permet a l’op ́erateur qui le con ̧coit d’intervenir manuellement au cours du d ́eveloppement
pour orienter la conception. On distingue principalement trois ́etapes : le placement des composants,
le routage des r ́eseaux et l’affectation des reseaux aux faces :

- L' ́etape de placement (placement, en anglais) consiste a positionner les composants sur le sup-port.
Cette ́etape est r ́ealis ́ee en essayant de disposer les composants au mieux les uns a cote des autres en fonction du fait qu’ils doivent ˆetre connect ́es entre eux.

- Etant donn ́ees les coordonn ́ees des points terminaux des composants et ayant connaissance de ceux qui doivent ˆetre reli ́es par un r ́eseau,l’ ́etape de routage (routing, en anglais) consiste a donner des emplacements pour des pistes reliant tous les points terminaux d’un meme reseau. En fait, la figure 1 indique un circuit a l’issue de l’etape de routage.

- L’ ́etape d’affectation des reseaux aux faces (layer assignment en anglais) consiste a ́eviter de faire chevaucher deux pistes de r ́eseaux diff ́erents. En effet, chaque reseau vehicule une infor-mation qui lui est propre et ne doit pas ˆetre connect ́e a un autre r ́eseau.

Heureusement, le support d’un circuit VLSI possedent une face sup ́erieure et une face inf ́erieure.

En fait, il est souvent impossible de faire circuler tous les r ́eseaux d’un circuit sur une seule surface sans que ceux-ci ne se chevauchent.

Les points terminaux des composants sont accessibles sur les faces
(en traversant le support), mais un segment de pistes n’est present que sur une des faces


Probleme de Via Minimization
Dans ce projet, nous allons nous int ́eresser a cette derniere ́etape de conception appelee affectation
des reseaux sur deux faces



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
- [X] Mieux documenter la page d'acceuil*
- [ ] Commencer a ecrire le rapport **
- [ ] Expliquer le probleme plus clairement***
- [X] fonctions de base (affichage, ajout, suppresion, liberation, initialisation)**
- [X] Imprementaion de l'algorithme de detection d'intersection**
  - [ ] Structure d'échéancier
  - [ ] Implementation de listes doublemenet chainé
  - [ ] Implementation de la methode de balayage
  - [ ] Implementation de l'Algorithme de Tri 
  - [ ] Structure d'Extrémité
- [ ] Detection de cycle impair***
- [X] Visualiser les circuits avec un fichier svg**
- [ ] mesure performance individuel des fonctions haut niveau (netlist , et les algo principeau)
  - [ ] Fichier test de clonage de reseau
  - [ ] Fichier test complexité fonctions individuel
  - [ ] Performance Balayge VS naiif
- [X] Collecte de ressource sur les different algorithme à utiliser*
- [ ] Ammelioration de la page web
- [ ] implementation des algos plus interessant (Genetic, Integer linear prog, heuristic)


## Ressources
<a href="http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.735.8064&rep=rep1&type=pdf">algo genetique</a><br/>
<a href="https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes">Latex pour le rapport finale</a><br/>
<a href="https://openclassrooms.com/fr/courses/1343806-pygtk/1343942-glade">Glade pour interface graphique facile</a><br/>
