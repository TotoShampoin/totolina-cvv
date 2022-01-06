#include <stdlib.h>
#include <stdio.h>
#include <Disp_TER.h>
#include <Control_TER.h>
#include <CVV/CVV.h>
#include <msleep.h>

int checkChipsValid(Game * game, char type, int line, int position) {
    int check = 0b00000;
    for(int i=0; i<TABCHIPS_LEN; i++) {
        if(table_of_chips[i].chips.type == type) {
            check += 1;//type valid
            break;
        }
    }
    if( line > 0 && line <= NBLINE ) check += 2; //line valide
    if( position > 0 && position <= NBPOS ) check += 4; //position valide
    if( areaAvailable(game, line, position) ) check += 8;  //case libre
    if( game->money >= getChipsFromType(type)->chips.price ) check += 16; //montant sufisant
    return check;
}

void prompt(Game * game) {
    dispUpcomingWave(game->virus);
    dispGame(game);
    dispChipsPrompt(game->money);
    dispChipsPrices();
}

int mainTER() {
    char lvl[256];
    printf("Level file name (lvl000.txt) : ");
    scanf(" %s", lvl);
    int keep_buying = 1, error = 0b11111, end_code = 0;
    char type; int line, position;
    Game * game = malloc(sizeof(Game));
    openGame(game, lvl);
    do {
        clear();
        dispError(error);
        prompt(game);
        keep_buying = (inputChips(&type, &line, &position) || !promptFinish());
        if(!keep_buying) break;
        if(0b11111 != (error = checkChipsValid(game, type, line, position))) {
            continue;
        }
        if(!promptConfirm(type, line, position)) continue;
        Chips * tmp = createAndPlaceChips(type, line, position);
        appendChips(&(game->chips), tmp);
        game->money -= tmp->price;
    } while(keep_buying);
    game->turn = 1;
    while(!(end_code = isGameOver(game->virus))) {
        spawnVirus(game);
        clear();
        dispTurn(game->turn);
        dispGame(game);
        msleep(INTERVAL);
        gameTurn(game);
        game->turn ++;
    };
    clear();
    dispTurn(game->turn);
    dispGame(game);
    switch (end_code) {
    case 1:
        printf("You have eliminated all viruses !\n");
        break;
    case 2:
        printf("The viruses have infected your computer ...\n");
        break;
    default:
        printf("The game is over\n");
        break;
    }
    return 1;
}