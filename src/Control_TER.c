#include <stdlib.h>
#include <Disp_TER.h>
#include <Control_TER.h>
#include <CVV/CVV.h>
#include <msleep.h>

int checkChipsValid(Game * game, char type, int line, int position) {
    int check = 0b00000;
    for(int i=0; i<TABCHIPS_LEN; i++) {
        if(table_of_chips[i].chips.type == type) {
            check += 1;
            break;
        }
    }
    if( line > 0 && line <= NBLINE ) check += 2;
    if( position > 0 && position <= NBPOS ) check += 4;
    if( areaAvailable(game, line, position) ) check += 8;
    if( game->money >= getChipsFromType(type)->chips.price ) check += 16;
    return check == 0b11111;
}

Chips * createAndPlaceChips(char type, int line, int position) {
    Chips * tmp = createChipsFromType(type);
    tmp->line = line; tmp->position = position;
    return tmp;
}

void prompt(Game * game) {
    clear();
    dispUpcomingWave(game->virus);
    dispGame(game);
    dispChipsPrompt(game->money);
    dispChipsPrices();
}

int mainTER() {
    int keep_buying = 1;
    char type; int line, position;
    Game * game = malloc(sizeof(Game));
    openGame(game, "lvl000.txt");
    do {
        prompt(game);
        keep_buying = (inputChips(&type, &line, &position) || !promptFinish());
        if(!checkChipsValid(game, type, line, position)) {
            dispError(0);
            dispChipsPrompt(game->money);
            continue;
        }
        if(!promptConfirm(type, line, position)) continue;
        Chips * tmp = createAndPlaceChips(type, line, position);
        appendChips(&(game->chips), tmp);
        game->money -= tmp->price;
    } while(keep_buying);
    game->turn = 1;
    while(!isGameOver(game->virus)) {
        spawnVirus(game);
        clear();
        dispTurn(game);
        dispGame(game);
        msleep(1500);
        gameTurn(game);
        game->turn ++;
    };
}