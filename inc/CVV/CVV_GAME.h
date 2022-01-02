#include <CVV/CVV_TYPE.h>
#ifndef __CVV_GAME

int areaAvailable(Game * G, int line, int position);

int chipsShootVirus(Chips * this_chips, Virus * virus_list);

int virusEatChips(Virus * this_virus, Chips * chips_list);

int virusMove(Virus * this_virus, Chips * chips_list);

int actionChips(Game * game);

int actionVirus(Game * game);

int spawnVirus(Game * game);

int removeDeadChips(Chips ** chips_list);

int removeDeadVirus(Virus ** virus_list);

int gameTurn(Game * game);

int initGame(Game ** game);

int isGameOver(Virus * virus);

#define __CVV_GAME
#endif