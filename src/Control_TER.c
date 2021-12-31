#include <stdlib.h>
#include <Disp_TER.h>
#include <Control_TER.h>
#include <CVV/CVV.h>

int checkChipsValid(Game * game, char type, int line, int position) {
    int check = 0b000;
    for(int i=0; i<TABCHIPS_LEN; i++) {
        if(table_of_chips[i].chips.type == type) {
            check += 1;
            break;
        }
    }
    if( line > 0 && line <= NBLINE ) check += 2;
    if( position > 0 && position <= NBPOS ) check += 4;
    if( areaAvailable(game, line, position) ) check += 8;
    return check == 0b1111;
}

int mainTER() {
    char type; int line, position;
    Game * game = malloc(sizeof(Game));
    openGame(game, "lvl000.txt");
    dispUpcomingWave(game->virus);
    dispChipsPrompt(game->money);
    dispChipsPrices();
    while(inputChips(&type, &line, &position) || !promptFinish()) {
        if(!checkChipsValid(game, type, line, position)) {
            dispError(0);
            dispChipsPrompt(game->money);
            continue;
        }
        if(!promptConfirm(type, line, position)) continue;
        Chips * tmp = createChipsFromType(type);
        tmp->line = line; tmp->position = position;
        appendChips(&(game->chips), tmp);
        game->money -= tmp->price;
        dispGame(game);
        dispChipsPrompt(game->money);
    }
}