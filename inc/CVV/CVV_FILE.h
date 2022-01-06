#include <CVV/CVV_TYPE.h>
#include <stdio.h>
#ifndef __CVV_FILE

/**
 * @brief Lis les caractères contenu dans file, jusqu'à atteindre un retour à la ligne
 * 
 * @param line Chaîne de caractères qui contiendra la ligne lue
 * @param len Longueur de line, pour éviter un SegFault
 * @param file Fichier à lire
 * @return Indicateur de fin de fichier
 */
int getLine(char * line, int len, FILE * file);

/**
 * @brief Convertie la ligne du fichier en Virus
 * 
 * @param data Ligne du fichier contenant les données du Virus (son type et ses coordonnées)
 * @return Le Virus créé par la conversion
 */
Virus * parseVirus(const char * data);

/**
 * @brief Lis tout le fichier pour initialiser le plateau de jeu
 * 
 * @param game Le plateau de jeu
 * @param file Le fichier à lire
 */
void loadGame(Game * game, FILE * file);

/**
 * @brief Exécute les fonctions de lecture de fichier et d'initialisation du jeu
 * 
 * @param game Le plateau de jeu
 * @param nom_du_fichier Le nom du fichier à lire
 * @return 0 si le fichier existe, 1 sinon
 */
int openGame(Game * game, const char * nom_du_fichier);

#define __CVV_FILE
#endif