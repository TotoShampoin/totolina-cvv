#include <stdio.h>
#include <stdlib.h>
#include <Control_TER.h>
#include <Control_MLV.h>

int main(int argc, char const *argv[]) {
    // char lvl[256];
    // printf("Level file name (lvl000.txt) : ");
    // scanf(" %s", lvl);
    initTables();
    // mainTER(lvl);
    mainMLV();
    return 0;
}
