#include <stdio.h>
#include <string.h>
#include <Disp_TER.h>

void clear() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void getChipsString(char * str, Chips * chips) {
    char s[ELMT_STR_LEN+1];
    sprintf(s, "%c%d", chips->type, chips->life);
    sprintf(str, "%-*s", ELMT_STR_LEN, s);
}

void getVirusString(char * str, Virus * virus) {
    char s[ELMT_STR_LEN+1];
    sprintf(s ,"%d%c", virus->life , virus->type);
    sprintf(str, "%*s", ELMT_STR_LEN, s);
}

void dispUpcomingWave(Virus * VL) {
    char t [NBLINE][NBPOS];
    int l, p;
    for(l=0; l<NBLINE; l++) {
        for(p=0; p<NBPOS; p++) {
            t[l][p] = ' ';
        }
    }
    while(VL != NULL) {
        t[VL->line-1][VL->turn-1] = VL->type;
        VL = VL->next;
    }
    printf("A wave of viruses are approaching...\n");
    for(l=0; l<NBLINE; l++) {
        printf("\t%d| ", l);
        for(p=0; p<NBPOS; p++) {
            printf(" %c", t[l][p]);
        }
        printf("\n");
    }
}

void dispChipsPrices() {
    printf("\t  | price | name     | power | life \n");
    for(int i=0; i<TABCHIPS_LEN; i++) {
        printf("\t%c : $%4d   %-8s   %5d   %4d \n", table_of_chips[i].chips.type, table_of_chips[i].chips.price, table_of_chips[i].nom, table_of_chips[i].chips.power, table_of_chips[i].chips.life);
    }
    printf("\n\tq : Finish \n");
    printf("\n");
}

void dispChipsPrompt(int current_price) {
    printf("Purse: %d BitCoins\nEnter the chips, followed by its line (1-%d) and position (1-%d)\n", current_price, NBLINE, NBPOS);
}

void dispTurn(Game * game) {
    printf("Game turn %d\n\n", game->turn);
}

void dispError(int type) {
    switch (type) {
    case 0: default:
        printf("Invalid input\n");
        break;
    }
}

void dispGame(Game * game) {
    char t [NBLINE][NBPOS][ELMT_STR_LEN+1];
    for(int l=0; l<NBLINE; l++) {
        for(int p=0; p<NBPOS; p++) {
            sprintf(t[l][p], "%*s", ELMT_STR_LEN, " ");
        }
    }
    Chips * tmpc = game->chips; Virus * tmpv = game->virus;
    while(tmpc != NULL) {
        getChipsString(t[tmpc->line-1][tmpc->position-1], tmpc);
        tmpc = tmpc->next;
    }
    while(tmpv != NULL) {
        if(tmpv->position != OOB) 
            getVirusString(t[tmpv->line-1][tmpv->position-1], tmpv);
        tmpv = tmpv->next;
    }
    for(int l=0; l<NBLINE; l++) {
        printf("%d | ", l+1);
        for(int p=0; p<NBPOS; p++) {
            printf("%s ", t[l][p]);
        }
        printf("\n");
    }
}

int  inputChips(char * type, int * line, int * position) {
    scanf(" %c", type);
    if(*type == 'q') return 0;
    scanf(" %d %d", line, position);
    return 1;
}

int promptConfirm(char type, int line, int position) {
    char answer;
    ChipsData * chp = getChipsFromType(type);
    printf("Want to continue your purchace ?\n");
    printf("\tprice | name     | line | position \n"
            "\t$%4d   %-8s   %-4d   %-8d \n"
            "(Y|N)",
        chp->chips.price, chp->nom, line, position);
    scanf(" %c", &answer);
    switch (answer) {
    case 'Y': case 'y': case 'O': case 'o':
        return 1;
    default: case 'N': case 'n':
        return 0;
    }
}

int promptFinish() {
    char answer;
    printf("Are you satisfied with your setup ?\n\n(Y|N)");
    scanf(" %c", &answer);
    switch (answer) {
    case 'Y': case 'y': case 'O': case 'o':
        return 1;
    default: case 'N': case 'n':
        return 0;
    }
}