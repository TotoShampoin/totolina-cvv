#include <CVV_TYPE.h>
#ifndef __CVV_GAME

int chipsShootVirus(Chips * this_chips, Virus * virus_list);

int virusEatChips(Virus * this_virus, Chips * chips_list);

int virusMove(Virus * this_virus, Chips * chips_list);

int actionChips(Game * game);

int actionVirus(Game * game);

int spawnVirus(Game * game);

int removeDeadChips(Chips * chips_list);

int removeDeadVirus(Virus * virus_list);

int gameTurn(Game * game);

#define __CVV_GAME
#endif