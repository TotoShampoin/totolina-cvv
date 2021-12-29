#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CVV/CVV.h>
#include <Disp_TER.h>

int main(int argc, char const *argv[]) {
    initTables();
    Game * game = malloc(sizeof(Game));
    openGame(game, "niveau.txt");
    dispUpcomingWave(game->virus);
    return 0;
}
