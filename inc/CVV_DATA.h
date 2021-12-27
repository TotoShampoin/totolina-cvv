#include <CVV_TYPE.h>
#ifndef __CVV_DATA

Chips * allocChips();
int initChips(Chips * chips, ChipsType type, int line, int position, int life, int price, int power);
Chips * createChips(ChipsType type, int line, int position, int life, int price, int power);

int appendChips(Chips ** chips_list, Chips * this_chips);

Chips * shiftChips(Chips * prev_chips);

void freeChips(Chips * chips);


Virus * allocVirus();
int initVirus(Virus * virus, VirusType type, int line, int life, int speed, int turn, int power);
Virus * createVirus(VirusType type, int line, int life, int speed, int turn, int power);

int appendVirus(Virus ** virus_list, Virus * this_virus);

Virus * shiftVirus(Virus * prev_virus);

void freeVirus(Virus * virus);


#define __CVV_DATA
#endif