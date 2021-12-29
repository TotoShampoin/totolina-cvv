#ifndef __CVV_TYPE

#define OOB    -1
#define NBLINE  7
#define NBPOS  24

typedef enum {
    ALU = 'A',
    RAM = 'R',
    PMMU = 'P',
    Patchs = 'X',
    Firewall = 'F'
} ChipsType;

typedef enum {
    DivZero = 'E',
    DDOS = 'D',
    SegFault = 'S',
    MemCorrupt = 'M',
    Bug = 'B'
} VirusType;

typedef struct chips {
    ChipsType type;
    int life;
    int line;
    int position;
    int price;
    int power;
    struct chips* next;
} Chips;

typedef struct virus {
    VirusType type;
    int life;
    int line;
    int position;
    int speed;
    int turn;
    int power;
    struct virus* next;
    struct virus* next_line;
    struct virus* prev_line;
} Virus;

#define TABCHIPS_LEN 5
struct {
    Chips chips;
    char * nom;
} table_of_chips[TABCHIPS_LEN];
#define TABVIRUS_LEN 5
struct {
    Virus virus;
    char * nom;
} table_of_virus[TABVIRUS_LEN];

void initTables();
Chips * createChipsFromType(ChipsType type);
Virus * createVirusFromType(VirusType type);

typedef struct {
    Virus* virus;
    Chips* chips;
    int turn;
    int money;
} Game;

#define __CVV_TYPE
#endif