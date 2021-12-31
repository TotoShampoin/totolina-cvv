#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CVV/CVV.h>
#include <Control_TER.h>

int main(int argc, char const *argv[]) {
    initTables();
    mainTER();
    return 0;
}
