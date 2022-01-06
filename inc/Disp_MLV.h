#include <CVV/CVV_TYPE.h>
#ifndef CVV_DISP_MLV
#include <MLV/MLV_all.h>

#define WIDTH  640
#define HEIGTH 480

/**
 * Grid Offset | Market Offset | Wabe Offset | Logo Offset | Turn Offset | Error Offset
 * La position XY du coin haut gauche de la grille | du marché | de la vague | du logo | du tour | des erreurs
 */
#define GO_X 48
#define GO_Y 96
#define MO_X 32
#define MO_Y 320
#define VO_X 320
#define VO_Y 280
#define LO_X 24
#define LO_Y 16 
#define TO_X 320
#define TO_Y 64
#define EO_X 320
#define EO_Y 16

#define NOLIFE -1

#define TRANSPARENT 0x00000000

/**
 * @brief Ressources graphiques, sonores, et couleurs.
 */
struct {
    struct {                /** Les images */
        MLV_Image * lg;         /**< Le logo du jeu */
        MLV_Image * sp;         /**< Les icones des Chips et virus */
    } sprites;
    struct {                /** Les polices de caractères */
        MLV_Font * tn;          /**< Police miniature */
        MLV_Font * ma;          /**< Police principale */
        // MLV_Font * bg;          /**< Police grande (inutilisée) */
    } fonts;
    // struct {                // Les sons et musiques (inutilisées)
    //     MLV_Music * ms;         // La musique du jeu
    //     MLV_Sound * cs;         // Chips shoot
    //     MLV_Sound * vs;         // Virus shoot
    //     MLV_Sound * cd;         // Chips dead
    //     MLV_Sound * vd;         // Virus dead
    // } sounds;
    struct {                /** Les couleurs */
        MLV_Color bg;           /**< Arrière plan */
        MLV_Color ln;           /**< Ligne */
        MLV_Color tx;           /**< Texte */
        MLV_Color bx;           /**< Boîte de dialogue */
        MLV_Color bd;           /**< Bordure de boîte de dialogue */
    } colors;
} assets;
/**
 * @brief Charge les ressources et les met dans assets
 * 
 * @return succès de chargement
 */
int loadAssetsMLV();
int unloadAssetsMLV();

/**
 * @brief Initialisation de la fenêtre et des ressources graphiques
 * 
 * @return succès de chargement
 */
int initMLV();
int closeMLV();
int reinitMLV();

/**
 * @brief Efface l'écran et le colorie en bleu
 * 
 */
void clearScreenMLV();

/**
 * @brief Affiche un texte
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param text 
 * @param size Taille de la police (0, 1 ou 2)
 */
void dispStrMLV(int x, int y, char * text, int size);

/**
 * @brief Affiche un texte suivit d'un nombre
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param text Texte posé avant le nombre (sans espace)
 * @param number Le nombre
 * @param size Taille de la police (0, 1 ou 2)
 */
void dispIntMLV(int x, int y, char * text, int number, int size);

/**
 * @brief Affiche le tour
 */
void dispTurnMLV(int turn);

/**
 * @brief Affiche l'argent
 */
void dispMoneyMLV(int money);

/**
 * @brief Affiche le logo
 * 
 */
void dispLogoMLV();

/**
 * @brief Affiche les erreurs
 * 
 */
void dispErrorMLV(int error);

/**
 * @brief Affiche l'ndicateur de life, en nombre
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param life 
 */
void lifebarMLV(int x, int y, int life);

/**
 * @brief Place un Chips ou un virus
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param sprite 0 à 4: Chips | 5 à 9: Virus
 * @param life Indicateur de life ; Si -1 alors n'affiche pas de barre
 */
void putSpriteMLV(int x, int y, int sprite, int life);

/**
 * @brief Affiche la grille de jeu
 */
void dispGridMLV(Game * game);

/**
 * @brief Affiche le marché des Chips, sous la forme d'un tableau
 */
void dispMarketMLV();

/**
 * @brief Affiche la vague de virus qui arrive
 */
void dispUpcomingWaveMLV(Virus * virus_list);

typedef enum {NONE, SPRITE, CHIPS, VIRUS, DEBUG} InfoType;
/**
 * @brief (Avancé) Une petite boîte qui affiche les informations d'un élément pointée par la souris
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param type Type de donnée à afficher (Sprite, Chips, Virus, ou chaine de caractères)
 * @param data Virus * ou Chips * (un cast sera fait en fonction de type)
 * 
 * @return succès
 */
int showInfosMLV(int x, int y, InfoType type, void * data);

/**
 * @brief Affiche une boite de dialogue
 * 
 * @param input Si prompt = 2, texte de l'input
 * @param str Texte de la boite
 * @param prompt 0: [Ok] | 1: [Yes No] | 2: [Input]
 * @return Réponse
 */
int msgBoxMLV(char ** input, char * str, int prompt);

/**
 * @brief Récupère la position de la souris, ainsi que ses clics
 * 
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param buttons Masque dont chaque bit correspond à un bouton
 */
void fetchMousePositionMLV(int * x, int * y, char * buttons);

/**
 * @brief Détermine la position sur la grille à partir de la souris
 * 
 * @param line Line sur la grille
 * @param position Position sur la grille
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @return Si la souris détermine bien une position
 */
int getGridPositionFromMouseMLV(int * line, int * position, int x, int y);

/**
 * @brief Détermine le type du Chips pointé par la souris sur le marché à Chips, sous la forme de l'index sur la table des Chips
 * 
 * @param index index sur la table des Chips
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @return Si la souris détermine bien un type
 */
int getChipsIndexOnMarketFromMouseMLV(int * index, int x, int y);

/**
 * @brief Détermine le Virus pointé par la souris sur l'affichage de la vague
 * 
 * @param virus_list la liste de virus du jeu
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @return Le virus
 */
Virus * getVirusOnWaveFromMouseMLV(Virus * virus_list, int x, int y);

#define CVV_DISP_MLV
#endif