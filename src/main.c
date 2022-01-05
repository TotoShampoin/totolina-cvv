#include <stdio.h>
#include <stdlib.h>
#include <Control_TER.h>
#include <Control_MLV.h>

int main(int argc, char const *argv[]) {
    int mode = 0;
    do {
        printf("Quel mode choisissez vous ?\n\tTerminal: 1\n\tGraphique: 2\n> ");
        scanf("%d", &mode);
    } while(mode != 1 && mode != 2);
    initTables();
    if(mode == 1) mainTER();
    if(mode == 2) mainMLV();
    return 0;
}

