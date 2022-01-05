#include <stdio.h>
#include <CVV/CVV.h>
#include <Control_MLV.h>
#include <Disp_MLV.h>

typedef struct {
    int error;
    int mx;
    int my;
    int id;
} DataDisp;

int checkChipsValidMLV(Game * game, Chips* tmp) {
    int check = 0b00;
    check += (game->money >= tmp->price) << 0;
    check += areaAvailable(game, tmp->line, tmp->position) << 1;
    return check;
}

void displayMLV(Game * game, DataDisp data, int mode) {
    int error = data.error;
    int mx = data.mx; int my = data.my; int id = data.id;
    clearScreenMLV();
    dispLogoMLV();
    dispGridMLV(game);
    if(mode) {
        dispMoneyMLV(game->money);
        dispMarketMLV();
        dispUpcomingWaveMLV(game->virus);
        dispErrorMLV(error);
        if(id != -1) showInfosMLV(mx, my, SPRITE, &id);
    } else {
        dispTurnMLV(game->turn);
    }
}

Chips * getChipsFromCoordinates(Chips * CL, int line, int position) {
    while(CL != NULL) {
        if(CL->line == line && CL->position == position) return CL;
        CL = CL->next;
    } return NULL;
}

int buyChips(Game * game, int id, int line, int position, int * error) {
    Chips * tmp = createChipsFromIndex(id);
    tmp->line = line;
    tmp->position = position;
    if((*error = checkChipsValidMLV(game, tmp)) == 0b11) {
        appendChips(&game->chips, tmp);
        game->money -= tmp->price;
    }
    return 1;
}

int sellChips(Game * game, int line, int position) {
    Chips * tmp = game->chips;
    while(tmp != NULL) {
        if(tmp->line == line && tmp->position == position) {
            tmp->life = 0;
            game->money += tmp->price;
            break;
        }
        tmp = tmp->next;
    }
    removeDeadChips(&game->chips);
    return 1;
}

int mainMLV() {
    initMLV();
    char * lvl;
    msgBoxMLV(&lvl, "Enter the level file name\n(eg: lvl000.txt)", 2);

    Game * game = malloc(sizeof(Game));
    openGame(game, lvl);

    int mx, my; char mb;
    int id = -1, line = 0, position = 0;
    int is_mk = 0, is_gd = 0;
    Virus * is_vr = NULL; Chips * is_cp = NULL;
    int error = 0b11, end_code = 0;

    // char str[16];

    // MLV_play_music(assets.sounds.ms, 0.5, -1);
    while(1) {
        displayMLV(game, (DataDisp){error, mx, my, id}, 1);
        if(is_vr != NULL) showInfosMLV(mx, my, VIRUS, is_vr);
        if(is_cp != NULL) showInfosMLV(mx, my, CHIPS, is_cp);
        
        fetchMousePositionMLV(&mx, &my, &mb);
        is_gd = getGridPositionFromMouseMLV( &line , &position , mx , my );
        is_vr = getVirusOnWaveFromMouseMLV(game->virus, mx, my);
        is_cp = getChipsFromCoordinates(game->chips, line, position);
        if(!is_gd) is_cp = NULL;

        if( (mb >> 0) & 1 ) { // Si clic gauche
            is_mk = getChipsIndexOnMarketFromMouseMLV(&id, mx , my);
            if(id == TABCHIPS_LEN) {
                if(msgBoxMLV(NULL, "Are you satisfied with your setup ?", 1)) break;
            }
            if(is_gd && id > -1 && id < TABCHIPS_LEN ) {
                buyChips(game, id, line, position, &error);
            }
            if(!is_mk) id = -1;
        }
        if( (mb >> 2) & 1 ) {
            is_gd = getGridPositionFromMouseMLV( &line , &position , mx , my );
            if(is_gd) {
                sellChips(game, line, position);
                is_cp = NULL;
            }
        }
        MLV_update_window();
        MLV_wait_milliseconds(1000/48);
    }
    game->turn = 1;
    while(!(end_code = isGameOver(game->virus))){
        spawnVirus(game);
        displayMLV(game, (DataDisp){error, mx, my, id}, 0);
        MLV_update_window();
        MLV_wait_milliseconds(INTERVAL);
        gameTurn(game);
        game->turn ++;
    }
    switch(end_code) {
        case 1:
            msgBoxMLV(NULL, "You have eliminated all viruses !", 0);
            break ;
        case 2:
            msgBoxMLV(NULL, "The viruses have infected your computer ...", 0);
            break;
        default :
            msgBoxMLV(NULL, "The game is over", 0);
            break ;
    }
    MLV_update_window();
    return 1;
}

