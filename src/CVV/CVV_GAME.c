#include <stdlib.h>
#include "../../inc/CVV_GAME.h"

int chips_shoot_virus(Chips * C, Virus * VL) {
    while(VL != NULL){
        if ( C->line == VL->line && VL->prev_line == NULL) {
            VL-> life -= C-> power ;
        }
        VL = VL->next;
    }
    return 1;
}

int virus_mange_chips(Virus * V, Chips * CL) {
    while(CL != NULL) {
        if( CL->line == V->line && CL->position == V->position+1 ) {
            CL->life -= V->power;
        }
        CL = CL->next;
    }
    return 1;
}

int virus_avance(Virus * V, Chips * CL) {
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

int action_chips(Game * game) {
    Chips * C = game->chips;
    while( C != NULL ) {
        chips_shoot_virus(C, game->virus);
        C = C->next;
    };
    return 1;
}

int action_virus(Game * game) {
    Virus * V = game->virus;
    while( V != NULL ) {
        virus_mange_chips(V, game->chips);
        virus_avance(V, game->chips);
        V = V->next;
    }
}

int spawn_virus(Game * game) {
    Virus * VL = game->virus;
    while( VL != NULL && VL->turn <= game->turn ) {
        if( VL->turn == game->turn ) {
            VL->position = NBPOS;
        }
        VL = VL->next;
    }
}

int remove_dead_chips(Chips * CL) {
    Chips * prev = CL;
    while( CL != NULL ) {
        if( CL->life <= 0 ) {
            // retirer chips de la liste (+ free)
        }
        prev = CL;
        CL = CL->next;
    }
    return 1;
}

int remove_dead_virus(Virus * VL) {
    Virus * prev = VL;
    while( VL != NULL ) {
        if( VL->life <= 0 ) {
            // retirer virus de la liste (+ free)
        }
        prev = VL;
        VL = VL->next;
    }
    return 1;
}

int tour_jeu(Game * game) {
    spawn_virus(game);
    action_chips(game);
    action_virus(game);
    remove_dead_chips(game->chips);
    remove_dead_virus(game->virus);
    game->turn ++;
}
