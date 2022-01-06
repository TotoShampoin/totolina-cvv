#include <CVV/CVV_TYPE.h>
#ifndef __CVV_GAME

/**
 * @brief Indique si la place est libre pour un Chips ou non
 * 
 * @param game Le plateau de jeu
 * @param line La line
 * @param position La position
 * @return 1 = vrai , 0 = faux
 */
int areaAvailable(Game * game, int line, int position);

/**
 * @brief Exécute l'action du Chips sélectionné, qui est de retirer au life du Virus en face le montant power dudit Chips.
 * On notera qu'un Chips peut tirer à travers les autres Chips.
 * 
 * @param this_chips Le Chips qui exécute l'action
 * @param virus_list La liste dans laquelle se trouve le Virus affecté
 * @return 1
 */
int chipsShootVirus(Chips * this_chips, Virus * virus_list);

/**
 * @brief Exécute l'action du Virus sélectionné, qui est de retirer au life du Chips juste devant le montant power dudit Virus.
 * 
 * @param this_virus Le Virus qui exécute l'action
 * @param chips_list La liste dans laquelle se trouve le Chips affecté
 * @return 1
 */
int virusEatChips(Virus * this_virus, Chips * chips_list);

/**
 * @brief Fait se déplacer le Virus sélectionné de <speed> pas.
 * On notera qu'un Virus ne peut pas doubler son suivant sur la ligne, ni passer à travers un Chips se trouvant sur son chemin. On notera également qu'un Virus n'avancera pas s'il n'est pas sur le terrain (= si sa position est -1, ou OOB)
 * 
 * @param this_virus Le Virus qui avance
 * @param chips_list La liste dans laquelle se trouve l'éventuel Chips qui va bloquer le Virus
 * @return 1 si le Virus avance, 0 sinon
 */
int virusMove(Virus * this_virus, Chips * chips_list);

/**
 * @brief Fait exécuter à tous les Chips de la liste la fonction chipsShootVirus
 * 
 * @param game Le jeu, contenant la liste des Chips et la liste des Virus
 * @return 1 si la liste de Chips n'est pas vide, 0 sinon
 */
int actionChips(Game * game);

/**
 * @brief Fait exécuter à tous les Virus de la liste la fonction virusEatChips
 * 
 * @param game Le jeu, contenant la liste des Virus et la liste des Chips
 * @return 1 si la liste de Virus n'est pas vide, 0 sinon
 */
int actionVirus(Game * game);

/**
 * @brief Fait apparaître les Virus du tour présent sur le plateau de jeu (= les place à la position tout à droite)
 * 
 * @param game Le plateau de jeu, contenant les Virus et le tour actuel
 * @return 1 si la liste de Virus n'est pas vide, 0 sinon
 */
int spawnVirus(Game * game);

/**
 * @brief Parcoure la liste des Chips et supprime ceux dont life vaut 0 (y compris le premier de la liste)
 * 
 * @param chips_list Pointeur vers la liste des Chips
 * @return 1 si la liste de Chips n'est pas vide, 0 sinon
 */
int removeDeadChips(Chips ** chips_list);

/**
 * @brief Parcoure la liste des Virus et supprime ceux dont life vaut 0 (y compris le premier de la liste)
 * 
 * @param virus_list Pointeur vers la liste des Virus
 * @return 1 si la liste de Virus n'est pas vide, 0 sinon
 */
int removeDeadVirus(Virus ** virus_list);

/**
 * @brief Exécute un tour du jeu (actionChips, actionVirus, etc...)
 * 
 * @param game Le plateau de jeu
 * @return 1 si le plateau de jeu existe, 0 sinon
 */
int gameTurn(Game * game);

/**
 * @brief Indique si le jeu est terminé et qui a gagné, selon l'existence de la liste des virus, et leurs positions
 * 
 * @param virus la liste de virus
 * @return 1 si le joueur gagne, 2 si les virus gagnent, 0 sinon
 */
int isGameOver(Virus * virus);

/**
 * @brief Récupère un Chips à partir des coordonnées line-position
 * 
 * @param chips_list Liste de Chips 
 * @param line La line du Chips à chercher
 * @param position La position du Chips à chercher
 * @return Pointeur du Chips trouvé, ou NULL si pas trouvé
 */
Chips * getChipsFromCoordinates(Chips * chips_list, int line, int position);

#define __CVV_GAME
#endif