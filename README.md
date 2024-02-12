Le jeu de la vie est un automate cellulaire dont les règles ont été définies par J. Conway en 1970. L'état de l'automate à l'étape n est uniquement fonction de son état à l'étape n − 1. L'évolution de l'état d'une cellule dépend de l'état de ses 8 plus proches voisins. Dans l'automate de Conway, les règles sont les suivantes :

    Une cellule vide à l'étape n − 1 et ayant exactement 3 voisins sera occupée à l'étape suivante. (naissance liée à un environnement optimal)
    Une cellule occupée à l'étape n − 1 et ayant 2 ou 3 voisins sera maintenue à l'étape n sinon elle est vidée. (destruction par désertification ou surpopulation) C'est l'analogie entre ces règles et certains critères d'évolution de populations de bactéries qui a conduit à donner à cet automate le nom de jeu de la vie.(1)

Voici les règles du lancement des fonctionnements du projet "jeu de la vie":

    Lancement en mode texte:

make MODE=TEXTE

./bin/main grilles/grille(votre grille préférée).txt

Plus en détail:

La touche "entrée" pour évoluer la grille

La touche 'c' pour activer ou désactiver la mode cyclique/non-cyclique

La touche 'v' pour activer ou désactiver le vieillissement

La touche 'o' pour activer l'oscillation

La touche 'n' pour parcourrir une nouvelle grille

La touche 'q' pour quitter le jeu

    Lancement en mode graphique:

make

./bin/main grilles/grille(votre grille préférée).txt

Plus en détail:

Un clic droit de souris quitte le jeu

Un clic gauche de souris dans la fenêtre fasse évoluer la grille

La touche 'c' pour activer ou désactiver la mode cyclique/non-cyclique

La touche 'o' pour activer l'oscillation

La touche 'n' pour parcourrir une nouvelle grille

    Lors de changement de mode sur le terminal, il faut d'abord saisir la commande make clean pour qu'on puisse recompiler le projet avec la nouvelle mode.

Ressources :

    http://ressources.univ-lemans.fr/AccesLibre/UM/Pedago/physique/02/recre/conway.html

