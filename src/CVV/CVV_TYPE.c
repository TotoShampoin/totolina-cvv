#include <string.h>
#include <CVV/CVV.h>

void initTables() {
    struct {
        Chips chips;
        char * nom;
    } toc[TABCHIPS_LEN] = {
        {.chips = { .type = ALU      , .life =  2 , .price =  10 , .power = 1 }, .nom = "ALU"     },
        {.chips = { .type = RAM      , .life =  4 , .price =  24 , .power = 2 }, .nom = "RAM"     },
        {.chips = { .type = PMMU     , .life =  8 , .price =  56 , .power = 4 }, .nom = "PMMU"    },
        {.chips = { .type = Patchs   , .life = 24 , .price = 176 , .power = 0 }, .nom = "Patchs"  },
        {.chips = { .type = Firewall , .life = 64 , .price = 320 , .power = 0 }, .nom = "Firewall"}
    };
    struct {
        Virus virus;
        char * nom;
    } tov[TABVIRUS_LEN] = {
        {.virus = { .type = DivZero    , .life =  3 , .speed =   1 , .power = 1 }, .nom = "DivZero"    },
        {.virus = { .type = DDOS       , .life =  9 , .speed =   1 , .power = 2 }, .nom = "DDOS"       },
        {.virus = { .type = SegFault   , .life = 11 , .speed =   1 , .power = 1 }, .nom = "SegFault"   },
        {.virus = { .type = MemCorrupt , .life = 17 , .speed =   1 , .power = 1 }, .nom = "MemCorrupt" },
        {.virus = { .type = Bug        , .life = 21 , .speed =   1 , .power = 1 }, .nom = "Bug"        }
    };
    memcpy(table_of_chips, toc, sizeof(toc));
    memcpy(table_of_virus, tov, sizeof(tov));
}