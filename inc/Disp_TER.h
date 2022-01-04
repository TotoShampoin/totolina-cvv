#include <CVV/CVV_TYPE.h>

#ifndef CVV_DISP_TER
#define ELMT_STR_LEN 3

void clear();

void getChipsString(char * str, Chips * chips);

void getVirusString(char * str, Virus * virus);

void dispUpcomingWave(Virus * virus_list);

void dispChipsPrices();

void dispChipsPrompt(int current_price);

void dispError(int type);

void dispTurn(Game * game);

void dispGame(Game * game);

int  inputChips(char * type, int * line, int * position);

int promptConfirm(char type, int line, int position);

int promptFinish();

#define CVV_DISP_TER
#endif