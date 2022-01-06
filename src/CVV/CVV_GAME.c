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
        if ( C->line == VL->line && VL->prev_line == NULL && VL->position != OOB) {
            VL-> life -= C-> power ;
        }
        VL = VL->next;
    }
    return 1;
}

int virusEatChips(Virus * V, Chips * CL) {
    while(CL != NULL) {
        if( CL->line == V->line && CL->position == V->position-1 && V->life > 0 ) {
            CL->life -= V->power;
        }
        CL = CL->next;
    }
    return 1;
}

int virusMove(Virus * V, Chips * CL) {
    if( V->position > OOB ) {
        int will_advance = 1;
        while( CL !=NULL ) {
            if( V->line == CL->line && V->position - CL->position <= V->speed ) {
                V->position = CL->position + 1;
                will_advance = 0;
                break;
            }
            CL = CL->next ;
        }
        if( V->prev_line && V->position - V->prev_line->position <= V->speed ) {
            V->position = V->prev_line->position + 1;
            will_advance = 0;
        }
        if( will_advance ) V->position -= V->speed;
        return 1;
    } return 0;
}

int actionChips(Game * game) {
    if(game->chips == NULL) return 0;
    Chips * C = game->chips;
    while( C != NULL ) {
        chipsShootVirus(C, game->virus);
        C = C->next;
    };
    return 1;
}

int actionVirus(Game * game) {
    if(game->virus == NULL) return 0;
    Virus * V = game->virus;
    while( V != NULL ) {
        virusEatChips(V, game->chips);
        virusMove(V, game->chips);
        V = V->next;
    }
    return 1;
}

int spawnVirus(Game * game) {
    if(game->virus == NULL) return 0;
    Virus * VL = game->virus;
    while( VL != NULL && VL->turn <= game->turn ) {
        if( VL->turn == game->turn ) {
            VL->position = NBPOS;
            // Cette partie sert a s'assurer que les virus n'apparaissent pas a la meme case
            if(VL->prev_line) {
                while(VL->position <= VL->prev_line->position) {
                    VL->position++;
                }
            }
        }
        VL = VL->next;
    }
    return 1;
}

int removeDeadChips(Chips ** CL) {
    if(*CL == NULL) return 0;
    Chips * prev = *CL, * chips = *CL, * remover;
    while( prev->next != NULL ) {
        chips = prev->next;
        if( chips->life <= 0 ) {
            remover = shiftChips(prev);
            freeChips(remover);
            continue;
        }
        prev = chips;
    }
    if((*CL) != NULL && (*CL)->life <= 0) {
        chips = *CL;
        if(chips->next != NULL) *CL = chips->next;
        else *CL = NULL;
        freeChips(chips);
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
            continue;
        }
        prev = virus;
    }
    if((*VL) != NULL && (*VL)->life <= 0) {
        virus = *VL;
        if(virus->next_line != NULL) {
            virus->next_line->prev_line = NULL;
            virus->next_line = NULL;
        }
        if(virus->next != NULL) *VL = virus->next;
        else *VL = NULL;
        freeVirus(virus);
    }
    return 1;
}

int gameTurn(Game * game) {
    if(game == NULL) return 0;
    actionChips(game);
    actionVirus(game);
    removeDeadChips(&(game->chips));
    removeDeadVirus(&(game->virus));
    return 1;
}

int isGameOver( Virus *V){
    if ( V==NULL) return 1;
    while(V != NULL){
        if (V->position== 0) return 2;
        V= V->next ;
    } 
    return 0 ;
}

Chips * getChipsFromCoordinates(Chips * CL, int line, int position) {
    while(CL != NULL) {
        if(CL->line == line && CL->position == position) return CL;
        CL = CL->next;
    } return NULL;
}