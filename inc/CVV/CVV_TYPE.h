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
} table_of_chips[TABCHIPS_LEN] = {
    {.chips = { .type = ALU      , .life =  2 , .price =  10 , .power = 1 }, .nom = "ALU"     },
    {.chips = { .type = RAM      , .life =  4 , .price =  24 , .power = 2 }, .nom = "RAM"     },
    {.chips = { .type = PMMU     , .life =  8 , .price =  56 , .power = 4 }, .nom = "PMMU"    },
    {.chips = { .type = Patchs   , .life = 24 , .price = 176 , .power = 0 }, .nom = "Patchs"  },
    {.chips = { .type = Firewall , .life = 64 , .price = 320 , .power = 0 }, .nom = "Firewall"}
};
#define TABVIRUS_LEN 5
struct {
    Virus virus;
    char * nom;
} table_of_virus[TABVIRUS_LEN] = {
    {.virus = { .type = DivZero    , .life =  3 , .speed =   1 , .power = 1 }, .nom = "DivZero"    },
    {.virus = { .type = DDOS       , .life =  9 , .speed =   1 , .power = 2 }, .nom = "DDOS"       },
    {.virus = { .type = SegFault   , .life = 11 , .speed =   1 , .power = 1 }, .nom = "SegFault"   },
    {.virus = { .type = MemCorrupt , .life = 17 , .speed =   1 , .power = 1 }, .nom = "MemCorrupt" },
    {.virus = { .type = Bug        , .life = 21 , .speed =   1 , .power = 1 }, .nom = "Bug"        }
};

typedef struct {
    Virus* virus;
    Chips* chips;
    int turn;
    int money;
} Game;

#define __CVV_TYPE
#endif