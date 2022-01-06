#include <CVV/CVV_TYPE.h>

/**
 * @brief Affiche toute les informations dont le joueur a besoin tandis qu'il achète des Chips
 * 
 * @param game Le plateau de jeu
 */
void prompt(Game * game);

/**
 * @brief Indique si les infos entrées par le joueur sont valides pour un Chips ou non (version Terminal)
 * 
 * @param game Le plateau de jeu
 * @param type Le type de chips
 * @param line La line
 * @param position La position
 * @return Réponse sous la forme de 5 flags en bit :
 *      type de Chips valide | 
 *      line entre 1 et 7 | 
 *      position entre 1 et 24 | 
 *      place disponible | 
 *      suffisance d'argent 
 */
int checkChipsValid(Game * game, char type, int line, int position);

/**
 * @brief Le main de la version Terminal du jeu
 * 
 * @return 1
 */
int mainTER();

