#include <CVV/CVV_TYPE.h>

#ifndef CVV_DISP_TER
#define ELMT_STR_LEN 3

/**
 * @brief Nettoie le terminal
 * 
 */
void clear();

/**
 * @brief Crée la chaîne de caractères sous la forme [Lettre][Life] du chips indiqué
 * 
 * @param str La chaîne de caractères
 * @param chips Le chips indiqué
 */
void getChipsString(char * str, Chips * chips);

/**
 * @brief Crée la chaîne de caractères sous la forme [Life][Lettre] du virus indiqué
 * 
 * @param str La chaîne de caractères
 * @param virus Le virus indiqué
 */
void getVirusString(char * str, Virus * virus);

/**
 * @brief Affiche la vague de virus qui se prépare pour la partie
 * 
 * @param virus_list La liste de virus
 */
void dispUpcomingWave(Virus * virus_list);

/**
 * @brief Affiche le marché des Chips, sous la forme d'un tableau
 * 
 */
void dispChipsPrices();

/**
 * @brief Affiche l'argent du joueur, suivit du message d'instruction 
 * pour acheter un Chips
 * 
 * @param current_price L'argent du joueur (en $)
 */
void dispChipsPrompt(int current_price);

/**
 * @brief Affiche les messages d'erreurs
 * 
 * @param error Code d'erreur, sous la forme de 5 flags en binaire:
 *      type de Chips valide | 
 *      line entre 1 et 7 | 
 *      position entre 1 et 24 | 
 *      place disponible | 
 *      suffisance d'argent 
 */
void dispError(int error);

/**
 * @brief Affiche le numéro de tour du jeu
 * 
 * @param turn Numéro de tour du jeu
 */
void dispTurn(int turn);

/**
 * @brief Affiche la grille de jeu
 * 
 * @param game Le jeu, contenant les Chips et les Virus
 */
void dispGame(Game * game);

/**
 * @brief Prend en entrée le type de Chips, ainsi que ses coordonnées
 * 
 * @param type Le type de Chips
 * @param line La line du Chips
 * @param position La position du Chips
 * @return Si type = 'q', renvoie 0. Sinon, renvoie 1
 */
int  inputChips(char * type, int * line, int * position);

/**
 * @brief Demande au joueur s'il est certain de poursuivre son achat (Y/y/O/o | N/n)
 * 
 * @param type Le type de Chips
 * @param line La line du Chips
 * @param position La position du Chips
 * @return La réponse du joueur (1 ou 0)
 */
int promptConfirm(char type, int line, int position);

/**
 * @brief Demande au joueur s'il veut vraiment arrêtre d'acheter des Chips (Y/y/O/o | N/n)
 * 
 * @return La réponse du joueur (1 ou 0)
 */
int promptFinish();

#define CVV_DISP_TER
#endif