#include <CVV/CVV_TYPE.h>
#ifndef __CVV_DATA

/**
 * @brief Alloue une place mémoire pour un Chips
 * 
 * @return Le pointeur vers Chips (ou NULL si non disponible)
 */
Chips * allocChips();

/**
 * @brief Initialise le Chips avec les valeurs indiquées
 * 
 * @param chips Chips a initialiser
 * @param type 
 * @param line 
 * @param position 
 * @param life 
 * @param price 
 * @param power 
 * @return 1 si Chips est alloué, 0 sinon
 */
int initChips(Chips * chips, ChipsType type, int line, int position, int life, int price, int power);

/**
 * @brief Alloue et initialise un Chips tout à la fois
 * 
 * @param type 
 * @param line 
 * @param position 
 * @param life 
 * @param price 
 * @param power 
 * @return Le pointeur vers Chips (ou NULL si non disponible)
 */
Chips * createChips(ChipsType type, int line, int position, int life, int price, int power);

/**
 * @brief Crée un Chips prédéfini (voir CVV/CVV_TYPE) à partir du type et lui affecte line et position
 * 
 * @param type Type de Chips, référé par la table de Chips prédéfinis
 * @param line 
 * @param position 
 * @return Le pointeur vers Chips (ou NULL si non dispobible ou type invalide)
 */
Chips * createAndPlaceChips(char type, int line, int position);

/**
 * @brief Insère un Chips au bout de la liste (ou au début si la liste est vide)
 * 
 * @param chips_list Pointeur vers la liste affectée
 * @param this_chips Le Chips a insérer
 * @return 1 si le Chips, 0 sinon
 */
int appendChips(Chips ** chips_list, Chips * this_chips);

/**
 * @brief Extrait de la liste le Chips qui suit celui indiqué
 * 
 * @param prev_chips Le Chips dont on retire le suivant
 * @return Le Chips retiré
 */
Chips * shiftChips(Chips * prev_chips);

/**
 * @brief Libère la zone mémoire correspondant au Chips indiqué
 * 
 * @param chips Le Chips à libérer
 */
void freeChips(Chips * chips);

/**
 * @brief Alloue une place mémoire pour un Virus
 * 
 * @return Le pointeur vers Virus (ou NULL si non disponible)
 */
Virus * allocVirus();

/**
 * @brief Initialise le Virus avec les valeurs indiquées
 * 
 * @param virus Virus a initialiser
 * @param type 
 * @param line 
 * @param life 
 * @param speed 
 * @param turn 
 * @param power 
 * @return 1 si Virus est alloué, 0 sinon
 */
int initVirus(Virus * virus, VirusType type, int line, int life, int speed, int turn, int power);

/**
 * @brief Alloue et initialise un Virus tout à la fois
 * 
 * @param type 
 * @param line 
 * @param life 
 * @param speed 
 * @param turn 
 * @param power 
 * @return Le pointeur vers Virus (ou NULL si non disponible)
 */
Virus * createVirus(VirusType type, int line, int life, int speed, int turn, int power);

/**
 * @brief Insère un Virus au bout de la liste (ou au début si la liste est vide)
 * 
 * @param virus_list Pointeur vers la liste affectée
 * @param this_virus Le Virus a insérer
 * @return 1 si le Virus, 0 sinon
 */
int appendVirus(Virus ** virus_list, Virus * this_virus);

/**
 * @brief Extrait de la liste le Virus qui suit celui indiqué
 * 
 * @param prev_virus Le Virus dont on retire le suivant
 * @return Le Virus retiré
 */
Virus * shiftVirus(Virus * prev_virus);

/**
 * @brief Libère la zone mémoire correspondant au Virus indiqué
 * 
 * @param virus Le Virus à libérer
 */
void freeVirus(Virus * virus);


#define __CVV_DATA
#endif