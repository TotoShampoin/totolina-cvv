#include <stdio.h>
#include <stdlib.h>

#include <CVV/CVV_FILE.h>
#include <CVV/CVV_DATA.h>

int getLine(char * line, int len, FILE * f) {
    char c; int i = 0;
    while( (c = getc(f)) != '\n' && c != EOF && i < len ) {
        line[i] = c;
        i++;
    }
    line[i] = 0;
    return c != EOF;
}

Virus * parseVirus(const char * data) {
    int turn, line; char type;
    sscanf(data, " %d %d %c", &turn, &line, &type);
    Virus * tmp = createVirusFromType(type);
    tmp->line = line; 
    tmp->turn = turn;
    tmp->position = OOB;
    return tmp;
    // return createVirus(type, line, 3, 1, turn, 1);
}

void loadGame(Game * game, FILE * f) {
    char line[16];
    game->turn = 0;
    game->money = 0;
    game->chips = NULL;
    game->virus = NULL;
    getLine(line, 16, f);
    game->money = atoi(line);
    while(getLine(line, 16, f)) {
        appendVirus(&(game->virus), parseVirus(line));
    }
}

int openGame(Game * game, const char * nom_du_fichier) {
    char lvl[513];
    sprintf(lvl, "levels/%s", nom_du_fichier);
    FILE *f = fopen(lvl, "r");
    if(f==NULL) return 0;
    loadGame(game , f);
    fclose(f);
    return 1;
}