#include <stdlib.h>
#include <stdio.h>
#include <CVV/CVV_DATA.h>

Chips * allocChips() {
    Chips * C;
    if ( (C = (Chips*)malloc(sizeof(Chips))!=NULL)){
        return C;
    }
    else {
        fprintf(stderr,"No RAM available");
        exit(EXIT_FAILURE);
    }
}

int initChips(Chips * C, ChipsType type, int line, int position, int life, int price, int power) {
    if(C == NULL){return 0;}
    C->type = type ;
    C->line = line;
    C->life = life;
    C->position = position;
    C->price = price;
    C->power = power;
    C->next = NULL;
    return 1;
}

Chips * createChips(ChipsType type, int line, int position, int life, int price, int power) {
    Chips *C =allocChips();
    initChips(C ,type, line, life, position, price, power);
    return C;
}

int appendChips(Chips ** CL, Chips * C) {
    if ( C==NULL)return 0;
    if (*CL == NULL){
        *CL= C;
        return 1;
    }
    Chips * tmp_c = *CL;
    while( tmp_c->next != NULL ) {
        tmp_c = tmp_c->next;
    }
    tmp_c->next = C;
    return 1 ;
}

Chips * shiftChips(Chips * PC) {
    Chips *C , *NC;
    if(PC->next != NULL) C = PC->next; else return NULL; 
    if(C->next != NULL) NC = C->next; else NC = NULL; 
    PC->next = NC;
    C->next =NULL;
    return C ;
}

void freeChips(Chips * C) {
    if(C !=NULL) free(C);
}


Virus * allocVirus() {
    Virus * V;
    if( (V = (Virus *) malloc(sizeof(Virus))) != NULL ) return V;
    fprintf(stderr, "No RAM available");
    exit(EXIT_FAILURE);
}

int initVirus(Virus * V, VirusType type, int line, int life, int speed, int turn, int power) {
    if( V == NULL ) return 0;
    V->type      = type;
    V->life      = life;
    V->line      = line;
    V->position  = OOB;
    V->speed     = speed;
    V->turn      = turn;
    V->power     = power;
    V->next      = NULL;
    V->next_line = NULL;
    V->prev_line = NULL;
    return 1;
}

Virus * createVirus(VirusType type, int line, int life, int speed, int turn, int power) {
    Virus * V = allocVirus();
    initVirus(V, type, line, life, speed, turn, power);
    return V;
}

int appendVirus(Virus ** VL, Virus * V) {
    if( V == NULL ) return 0;
    if( *VL == NULL ) {
        *VL = V;
        return 1;
    }
    Virus * tmp_c = *VL;
    Virus * tmp_l = NULL;
    while( tmp_c->next != NULL ) {
        if( tmp_c->line == V->line && tmp_c->next_line == NULL ) tmp_l = tmp_c;
        tmp_c = tmp_c->next;
    }
    tmp_c->next = V;
    if( tmp_l != NULL ) {
        V->prev_line = tmp_l;
        tmp_l->next_line = V;
    }
    return 1;
}

Virus * shiftVirus(Virus * PV) {
    Virus * V, * NV = NULL;
    Virus * VNL = NULL, * VPL = NULL;
    if(PV->next) V = PV->next; else return NULL;
    if(V->next) NV = V->next;
    if(V->next_line) VNL = V->next_line;
    if(V->prev_line) VPL = V->prev_line;
    PV->next = NV;
    VNL->prev_line = VPL;
    VPL->next_line = VNL;
    V->next = NULL;
    V->next_line = NULL;
    V->prev_line = NULL;
    return V;
}

void freeVirus(Virus * V) {
    if( V != NULL ) free( V );
}