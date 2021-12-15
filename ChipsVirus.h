typedef enum {
    ALU,
    RAM,
    PMMU,
    Patchs,
    Firewall
} ChipsType;

typedef enum {
    DivZero,
    DDOS,
    SegFault,
    MemCorrupt,
    Bug
} VirusType;

typedef struct chips {
    ChipsType type;
    int life;
    int line;
    int position;
    int price;
    struct chips* next;
} Chips;

typedef struct virus {
    VirusType type;
    int life;
    int line;
    int position;
    int speed;
    int turn;
    struct virus* next;
    struct virus* next_line;
    struct virus* prev_line;
} Virus;

typedef struct {
    Virus* virus;
    Chips* chips;
    int turn;
    int money;
} Game;

