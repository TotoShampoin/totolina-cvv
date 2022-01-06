#ifndef __CVV_TYPE

#define OOB    -1
#define NBLINE  7
#define NBPOS  24

/**
 * @brief Le type de Chips, sous forme d'un caractère
 */
typedef enum {
    ALU = 'A',
    RAM = 'R',
    PMMU = 'P',
    Patchs = 'X',
    Firewall = 'F'
} ChipsType;

/**
 * @brief Le type de Virus, sous forme d'un caractère
 */
typedef enum {
    DivZero = 'E',
    DDOS = 'D',
    SegFault = 'S',
    MemCorrupt = 'M',
    Bug = 'B'
} VirusType;

/**
 * @brief Structure d'un Chips
 * 
 */
typedef struct chips {
    ChipsType type;     /**< Type de Chips */
    int life;           /**< Nombre de points de vies */
    int line;           /**< Coordonnée verticale */
    int position;       /**< Coordonnée horizontale */
    int price;          /**< Prix du Chips */
    int power;          /**< Puissance de tir */
    struct chips* next; /**< Suivant sur la liste */
} Chips;

/**
 * @brief Structure d'un Virus
 * 
 */
typedef struct virus {
    VirusType type;             /**< Type de Virus */
    int life;                   /**< Nombre de points de vies */
    int line;                   /**< Coordonnée verticale */
    int position;               /**< Coordonnée horizontale */
    int speed;                  /**< Vitesse de déplacement */
    int turn;                   /**< Tour d'apparition */
    int power;                  /**< Puissance de tir */
    struct virus* next;         /**< Suivant sur la liste */
    struct virus* next_line;    /**< Suivant sur la ligne */
    struct virus* prev_line;    /**< Précédent sur la ligne */
} Virus;

/**
 * @brief Structure d'une donnée de Chips prédéfini (contenant le Chips et le nom de son type)
 * 
 */
typedef struct {
    Chips chips;
    char * nom;
} ChipsData;

/**
 * @brief Structure d'une donnée de Virus prédéfini (contenant le Virus et le nom de son type)
 * 
 */
typedef struct {
    Virus virus;
    char * nom;
} VirusData;

#define TABCHIPS_LEN 5
#define TABVIRUS_LEN 5
/**
 * @brief Table des Chips prédéfinis
 * 
 */
ChipsData table_of_chips[TABCHIPS_LEN];
/**
 * @brief Table des Virus prédéfinis
 * 
 */
VirusData table_of_virus[TABVIRUS_LEN];

/**
 * @brief Initialise les tables de Chips et Virus prédéfinis
 * 
 */
void initTables();

/**
 * @brief Cherche le Chips prédéfini à partir du type, et renvoie son index dans la table
 * 
 * @param type Le type de Chips recherché
 * @return index dans la table de Chips, ou la longueur de la table si le type n'existe pas
 */

int getChipsIndexFromType(ChipsType type);
/**
 * @brief Cherche le Virus prédéfini à partir du type, et renvoie son index dans la table
 * 
 * @param type Le type de Virus recherché
 * @return index dans la table de Virus, ou la longueur de la table si le type n'existe pas
 */
int getVirusIndexFromType(VirusType type);

/**
 * @brief Cherche le Chips prédéfini à partir du type, et renvoie son ChipsData
 * 
 * @param type Le type de Chips recherché
 * @return Pointeur du ChipsData, ou NULL si le type n'existe pas
 */
ChipsData * getChipsFromType(ChipsType type);

/**
 * @brief Cherche le Virus prédéfini à partir du type, et renvoie son VirusData
 * 
 * @param type Le type de Virus recherché
 * @return Pointeur du VirusData, ou NULL si le type n'existe pas
 */
VirusData * getVirusFromType(VirusType type);

/**
 * @brief Cherche le Chips prédéfini à partir du type, et en renvoie une copie
 * 
 * @param type Le type de Chips recherché
 * @return Pointeur du Chips copié, ou NULL si le type n'existe pas
 */
Chips * createChipsFromType(ChipsType type);

/**
 * @brief Cherche le Virus prédéfini à partir du type, et en renvoie une copie
 * 
 * @param type Le type de Virus recherché
 * @return Pointeur du Virus copié, ou NULL si le type n'existe pas
 */
Virus * createVirusFromType(VirusType type);

/**
 * @brief Cherche le Chips prédéfini à partir de son index dans la table, et en renvoie une copie
 * 
 * @param index L'index du Chips dans la table
 * @return Pointeur du Chips copié, ou NULL si l'index est invalide
 */
Chips * createChipsFromIndex(int index);

/**
 * @brief Cherche le Virus prédéfini à partir de son index dans la table, et en renvoie une copie
 * 
 * @param index L'index du Virus dans la table
 * @return Pointeur du Virus copié, ou NULL si l'index est invalide
 */
Virus * createVirusFromInedx(int index);

/**
 * @brief Structure d'un plateau de jeu
 * 
 */
typedef struct {
    Virus* virus;
    Chips* chips;
    int turn;
    int money;
} Game;

#define __CVV_TYPE
#endif