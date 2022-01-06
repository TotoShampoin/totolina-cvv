# Projet - Chips vs Virus
Par Thomas Garnier et Lina Guerroui, en 2021-2022

Chips vs Virus est un tower-defense largement inspiré de Plants vs Zombies.

## Règles du jeu

Le jeu présente au joueur une vague de Virus qui s'apprète à envahir son réseau informatique. Son but est d'acheter des défenses (ou Chips) qui vont bloquer et anhéantir ces Virus.

Le jeu commence par une première phase où le joueur peut acheter les Chips et les positionner, puis vient la deuxième phase où les Virus progressent sur le réseau informatique tandis que les Chips les attaquent.

La partie est terminée lorsqu'un des Virus atteint l'autre bout du réseau (donc l'ordinateur du joueur), ou lorsque tous les Virus de la vague sont anhéantis.

## Comment jouer

Dans le répertoire du jeu (`./bin`), entrer `./cvv`.

Le jeu demandera alors au joueur s'il veut jouer en mode Terminal ou en mode Graphique.

Dans les deux cas, vous pourrez entrer le nom du niveau que vous voulez jouer. Voici une liste des niveaux disponibles dans le dossier level:
 - lvl000.txt
 - lvl001.txt
 - testall.txt (niveau un peu bac-à-sable)

### Mode Terminal

Entrer respectivement la lettre du Chips, sa ligne, et sa colonne. Valider son choix avec `Y`, ou `N` pour ne pas valider.

Pour terminer la phase d'achat, entrer `q`, puis valider avec `Y`.

Note: Il est possible d'entrer une série de Chips, séparés chacun par un `Y`. 
> `A 1 1 Y A 2 1 Y A 3 Y`
>
> Crée un Chips sur les lignes 1, 2 et 3, à la première colonne.

### Mode Graphique

Cliquer sur un des Chips de la table en bas à gauche, puis cliquer sur une case de la grille au dessus pour placer un Chips.

Faire un clic droit sur un des Chips de la grille pour vendre celle-ci.

Pour terminer la phase d'achat, cliquer sur "Finish", puis valider via la boîte de dialogue qui s'affiche.

## Comment compiler

Dans le répertoire du projet (parent au dossier `bin`), exécuter la commande `make`.