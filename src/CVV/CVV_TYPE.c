#include <string.h>
#include <CVV/CVV.h>

void initTables() {  //a expliquer dans le rapport
    table_of_chips[0].nom = "ALU";
        table_of_chips[0].chips.type  = ALU;
        table_of_chips[0].chips.life  =   2;
        table_of_chips[0].chips.power =   1;
        table_of_chips[0].chips.price =  10;
    table_of_chips[1].nom = "RAM";
        table_of_chips[1].chips.type  = RAM;
        table_of_chips[1].chips.life  =   4;
        table_of_chips[1].chips.power =   2;
        table_of_chips[1].chips.price =  24;
    table_of_chips[2].nom = "PMMU";
        table_of_chips[2].chips.type  = PMMU;
        table_of_chips[2].chips.life  =    8;
        table_of_chips[2].chips.power =    4;
        table_of_chips[2].chips.price =   56;
    table_of_chips[3].nom = "Patchs";
        table_of_chips[3].chips.type  = Patchs;
        table_of_chips[3].chips.life  =     24;
        table_of_chips[3].chips.power =      0;
        table_of_chips[3].chips.price =    176;
    table_of_chips[4].nom = "Firewall";
        table_of_chips[4].chips.type  = Firewall;
        table_of_chips[4].chips.life  =       64;
        table_of_chips[4].chips.power =        0;
        table_of_chips[4].chips.price =      320;
    table_of_virus[0].nom = "DivZero";
        table_of_virus[0].virus.type  = DivZero;
        table_of_virus[0].virus.life  =       3;
        table_of_virus[0].virus.power =       1;
        table_of_virus[0].virus.speed =       1;
    table_of_virus[1].nom = "DDOS";
        table_of_virus[1].virus.type  = DDOS;
        table_of_virus[1].virus.life  =    9;
        table_of_virus[1].virus.power =    2;
        table_of_virus[1].virus.speed =    1;
    table_of_virus[2].nom = "SegFault";
        table_of_virus[2].virus.type  = SegFault;
        table_of_virus[2].virus.life  =       11;
        table_of_virus[2].virus.power =        1;
        table_of_virus[2].virus.speed =        1;
    table_of_virus[3].nom = "MemCorrupt";
        table_of_virus[3].virus.type  = MemCorrupt;
        table_of_virus[3].virus.life  =         17;
        table_of_virus[3].virus.power =          1;
        table_of_virus[3].virus.speed =          1;
    table_of_virus[4].nom = "Bug";
        table_of_virus[4].virus.type  = Bug;
        table_of_virus[4].virus.life  =  21;
        table_of_virus[4].virus.power =   1;
        table_of_virus[4].virus.speed =   1;
}

ChipsData * getChipsFromType(ChipsType type) {
    ChipsData * typ;
    int i = 0;
    do {
        typ = &(table_of_chips[i]);
        i++;
    } while(typ->chips.type != type && i < TABCHIPS_LEN);
    return typ;
}

VirusData * getVirusFromType(VirusType type) {
    VirusData * typ;
    int i = 0;
    do {
        typ = &(table_of_virus[i]);
        i++;
    } while(typ->virus.type != type && i < TABCHIPS_LEN);
    return typ;
}

Chips * createChipsFromType(ChipsType type) {
    Chips * tmp = allocChips();
    ChipsData * dat = getChipsFromType(type);
    if(tmp == NULL || dat == NULL) return NULL;
    Chips * typ = &(dat->chips);
    memcpy(tmp, typ, sizeof(Chips));
    return tmp;
}

Virus * createVirusFromType(VirusType type) {
    Virus * tmp = allocVirus();
    VirusData * dat = getVirusFromType(type);
    if(tmp == NULL || dat == NULL) return NULL;
    Virus * typ = &(dat->virus);
    memcpy(tmp, typ, sizeof(Virus));
    return tmp;
}
