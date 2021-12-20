#include "CVV_TYPE.h"
#ifndef __CVV_GAME

int chips_shoot_virus(Chips * this_chips, Virus * virus_list);

int virus_mange_chips(Virus * this_virus, Chips * chips_list);

int virus_avance(Virus * this_virus, Chips * chips_list);

int action_chips(Game * game);

int action_virus(Game * game);

int spawn_virus(Game * game);

int remove_dead_chips(Chips * chips_list);

int remove_dead_virus(Virus * virus_list);

int tour_jeu(Game * game);

#define __CVV_GAME
#endif