#include <stdlib.h>
#include <CVV/CVV_GAME.h>
#include <CVV/CVV_DATA.h>

int areaAvailable(Game * G, int line, int position) {
    Chips * C = G->chips;
    while( C != NULL ) {
        if(C->line == line && C->position == position) return 0;
        C = C->next;
    }
    Virus * V = G->virus;
    while( V != NULL ) {
        if(V->line == line && V->position == position) return 0;
        V = V->next;
    }
    return 1;
}

int chipsShootVirus(Chips * C, Virus * VL) {
    while(VL != NULL){
        if ( C->line == VL->line && VL->prev_line == NULL) {
            VL-> life -= C-> power ;
        }
        VL = VL->next;
    }
    return 1;
}

int virusEatChips(Virus * V, Chips * CL) {
    while(CL != NULL) {
        if( CL->line == V->line && CL->position == V->position+1 ) {
            CL->life -= V->power;
        }
        CL = CL->next;
    }
    return 1;
}

int virusMove(Virus * V, Chips * CL) {
    if( V->position > -1 ) {
        int will_advance = 1;
        while( CL !=NULL ) {
            if( V->line == CL->line && V->position - CL->position < V->speed ) {
                V->position = CL->position + 1;
                will_advance = 0;
                break;
            }
            CL = CL->next ;
        }
        if( V->next_line && V->position - V->next_line->position < V->speed ) {
            V->position = V->next_line->position + 1;
            will_advance = 0;
        }
        if( will_advance ) V->position -= V->speed;
        return 1;
    } return 0;
}

int actionChips(Game * game) {
    Chips * C = game->chips;
    while( C != NULL ) {
        chipsShootVirus(C, game->virus);
        C = C->next;
    };
    return 1;
}

int actionVirus(Game * game) {
    Virus * V = game->virus;
    while( V != NULL ) {
        virusEatChips(V, game->chips);
        virusMove(V, game->chips);
        V = V->next;
    }
}

int spawnVirus(Game * game) {
    Virus * VL = game->virus;
    while( VL != NULL && VL->turn <= game->turn ) {
        if( VL->turn == game->turn ) {
            VL->position = NBPOS;
        }
        VL = VL->next;
    }
}

int removeDeadChips(Chips ** CL) {
    if(*CL == NULL) return 0;
    Chips * prev = *CL, * chips = *CL, * remover;
    while( prev->next != NULL ) {
        chips = prev->next;
        if( chips->life <= 0 ) {
            remover = shiftChips(prev);
            freeChips(remover);
        }
        prev = chips;
    }
    if((*CL)->life == 0) {
        freeChips(*CL);
        *CL = NULL;
    }
    return 1;
}

int removeDeadVirus(Virus ** VL) {
    if(*VL == NULL) return 0;
    Virus * prev = *VL, *virus = *VL, * remover;
    while( prev->next != NULL ) {
        virus = prev->next;
        if( virus->life <= 0 ) {
            remover = shiftVirus(prev);
            freeVirus(remover);
        }
        prev = virus;
    }
    if((*VL)->life == 0) {
        freeVirus(*VL);
        *VL = NULL;
    }
    return 1;
}

int gameTurn(Game * game) {
    spawnVirus(game);
    actionChips(game);
    actionVirus(game);
    removeDeadChips(&(game->chips));
    removeDeadVirus(&(game->virus));
    game->turn ++;
}

int initGame(Game ** game) {
    if(*game == NULL) *game = malloc(sizeof(Game));
}