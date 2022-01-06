#include <CVV/CVV_TYPE.h>

/**
 * @brief Structure de données à afficher, pour réduire artificiellement le nombre d'arguments de displayMLV
 * 
 */
typedef struct {
    int error;  /**< Code d'erreur */
    int mx;     /**< Coordonnée x de la souris */
    int my;     /**< Coordonnée y de la souris */
    int id;     /**< index du Chips que le joueur a l'intention d'acheter (pour afficher son icône à côté de la souris) */
} DataDisp;

/**
 * @brief Indique si les infos appelées par le joueur sont valides pour un Chips ou non (version Graphique)
 * 
 * @param game Le plateau de jeu
 * @param tmp Le Chips à insérer
 * @return Réponse sous la forme de 2 flags en bit :
 *      place disponible | 
 *      suffisance d'argent 
 */
int checkChipsValidMLV(Game * game, Chips* tmp);

/**
 * @brief Affiche l'écran du jeu
 * 
 * @param game Le plateau de jeu
 * @param data Les données supplémentaires (pointeur de souris, erreurs, id de Chips)
 * @param mode Mode achat de Chips ou non
 */
void displayMLV(Game * game, DataDisp data, int mode);

/**
 * @brief Achète un Chips à partir des données et l'insère, ou affecte le code d'erreur
 * @note Le Chips acheté est alloué, puis libéré si l'insertion est impossible
 * 
 * @param game Le plateau de jeu
 * @param id Index dans la table de Chips prédéfinis
 * @param line La line
 * @param position La position
 * @param error Le code d'erreur (voir checkChipsValidMLV)
 * @return 1
 */
int buyChips(Game * game, int id, int line, int position, int * error);

/**
 * @brief Retire le Chips pointé par les coordonnées line-position (qui est alors remboursé)
 * 
 * @param game Le plateau de jeu
 * @param line La line
 * @param position La position
 * @return 1
 */
int sellChips(Game * game, int line, int position);

/**
 * @brief Le main du mode graphique
 * 
 * @return int 
 */
int mainMLV();
