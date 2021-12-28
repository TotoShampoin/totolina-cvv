#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CVV/CVV.h>
#include <Disp_TER.h>


Chips * createChipsFromType(ChipsType type) {
    char str[ELMT_STR_LEN];
    Chips * tmp = allocChips(), * typ;
    int i = 0;
    do {
        typ = &(table_of_chips[i].chips);
        i++;
    } while(typ->type != type && i < TABCHIPS_LEN);
    memcpy(tmp, typ, sizeof(Chips));
    return tmp;
}

void dispChipsAll(Chips * C) {
    printf("\n");
    char str[ELMT_STR_LEN];
    while (C != NULL) {
        getChipsString(str, C); printf("%s ", str);
        C = C->next;
    }
    printf("\n");
}


int main(int argc, char const *argv[]) {
    initTables();
    char str[ELMT_STR_LEN];
    Chips * C = NULL;
    appendChips(&C, createChipsFromType(ALU     ));

    dispChipsAll(C);
    C->life = 0;
    dispChipsAll(C);
    removeDeadChips(&C);
    dispChipsAll(C);
    printf("\n");
    return 0;
}
