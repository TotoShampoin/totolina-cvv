#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CVV/CVV.h>
#include <Control_TER.h>

int main(int argc, char const *argv[]) {
    char lvl[256];
    printf("Level file name (lvl000.txt) : ");
    scanf(" %s", lvl);
    initTables();
    mainTER(lvl);
    return 0;
}
