#include <stdio.h>
#include <CVV/CVV.h>
#include <Control_MLV.h>
#include <Disp_MLV.h>

int checkChipsValidMLV(Game * game, Chips* tmp) {
    int check = 0b00;
    check += (game->money >= tmp->price) << 0;
    check += areaAvailable(game, tmp->line, tmp->position) << 1;
    return check;
}

int mainMLV() {
    Game * game = malloc(sizeof(Game));
    openGame(game, "lvl000.txt");

    int mx, my; char mb;
    int id = -1, line = 0, position = 0;
    int is_mk = 0, is_gd = 0;
    int error = 0b11;

    // char str[16];

    initMLV();
    while(1) {
        clearScreenMLV();
        
        // dispTurnMLV(game->turn);
        dispMoneyMLV(game->money);
        dispLogoMLV();
        dispGridMLV(game);
        dispMarketMLV();
        dispUpcomingWaveMLV(game->virus);
        dispErrorMLV(error);
        if(id != -1) showInfosMLV(mx, my, SPRITE, &id);
        
        fetchMousePositionMLV(&mx, &my, &mb);
        if( (mb >> 0) & 1 ) { // Si clic gauche
            is_mk = getChipsIndexOnMarketFromMouseMLV(&id, mx , my);
            is_gd = getGridPositionFromMouseMLV( &line , &position , mx , my );
            if(id == TABCHIPS_LEN) {
                break;
            }
            if(is_gd && id > -1 && id < TABCHIPS_LEN ) {
                Chips * tmp = createChipsFromIndex(id);
                tmp->line = line;
                tmp->position = position;
                if((error = checkChipsValidMLV(game, tmp)) == 0b11) {
                    appendChips(&game->chips, tmp);
                    game->money -= tmp->price;
                }
            }
            line = 0; position = 0;
            if(!is_mk) id = -1;
        }

        MLV_update_window();
        MLV_wait_milliseconds(1000/48);
    }

    return 1;
}

/**
 * placer le chips dans la grille 
 je vais cliquer la ou je veux le placer 
 
 * 
 */


        // if(is_mk) {
        //     sprintf(str, "%d", id);
        // } else if(is_gd) {
        //     sprintf(str, "%d %d", line, position);
        // } else {
        //     sprintf(str, "");
        // }
        // showInfosMLV(mx, my, DEBUG, str);