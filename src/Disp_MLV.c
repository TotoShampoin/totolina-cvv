#include <Disp_MLV.h>
#include <stdio.h>

//  J'ai ajouté deux fonctions dans CVV_TYPE : 
//      getChipsIndexFromType getVirusIndexFromType 
//  Ils servent à obtenir le numéro du chips/virus dans la table

int loadAssetsMLV() {
    assets.colors .bg   = 0x000055FF; // Bleu très foncé
    assets.colors .ln   = 0x0000AAFF; // Bleu foncé
    assets.colors .tx   = 0xFFFFFFFF; // Blanc
    assets.colors .bx   = 0x000000AA; // Noir transparent
    assets.colors .bd   = 0xFFFFFFAA; // Blanc transparent
    assets.sprites.lg   = MLV_load_image("assets/sprites/logo.png");
    assets.sprites.sp   = MLV_load_image("assets/sprites/sprites.png");
    assets.fonts  .ma   = MLV_load_font("assets/fonts/ps2p.ttf",  8);
    assets.fonts  .tn   = MLV_load_font("assets/fonts/sp7.ttf" ,  9); // C'est visuellement plus petit que .ma, mais la police est configurée comme ça
    assets.fonts  .bg   = MLV_load_font("assets/fonts/dos.ttf" , 16);
    assets.sounds .ms   = MLV_load_music("assets/sounds/lsac.wav");
    return 1;
}
int unloadAssetsMLV() {
    MLV_free_image(assets.sprites.lg); assets.sprites.lg = NULL;
    MLV_free_image(assets.sprites.sp); assets.sprites.sp = NULL;
    MLV_free_font (assets.fonts  .ma); assets.fonts  .ma = NULL;
    return 1;
}

int initMLV() {
    MLV_create_window("Chips vs Virus", "", WIDTH, HEIGTH);
    MLV_init_audio();
    loadAssetsMLV();
    return 1;
}
int closeMLV() {
    unloadAssetsMLV();
    MLV_free_window();
    return 1;
}
int reinitMLV() {
    closeMLV();
    initMLV();
    return 1;
}

void clearScreenMLV() {
    MLV_clear_window(assets.colors.bg);
}

void dispStrMLV(int x, int y, char * t, int s) { // Fonction d'affichage, pour rendre le code plus lisible
    switch (s) {
    case 0: // Petit
        MLV_draw_text_with_font(x, y, t, assets.fonts.tn, assets.colors.tx);
        break;
    case 1: default: // Normal
        MLV_draw_text_with_font(x, y, t, assets.fonts.ma, assets.colors.tx);
        break;
    case 2: // Grand
        MLV_draw_text_with_font(x, y, t, assets.fonts.bg, assets.colors.tx);
        break;
    }
}
void dispIntMLV(int x, int y, char * t, int n, int s) {
    char ms[32]; sprintf(ms, "%s%d", t, n);
    dispStrMLV(x, y, ms, s);
}

void dispTurnMLV(int t) {
    dispIntMLV(TO_X, TO_Y, "Game turn : ", t, 1);
}
void dispMoneyMLV(int m) {
    dispIntMLV(MO_X, MO_Y-40, "Money : $", m, 1);
}

void dispLogoMLV() {
    MLV_draw_image(assets.sprites.lg, LO_X, LO_Y);
}

// bit 0 = money
// bit 1 = place
void dispErrorMLV(int error) {
    if( !((error >> 0) & 1) ) {
        dispStrMLV(EO_X, EO_Y, "Not enough money", 1);
    }
    if( !((error >> 1) & 1) ) {
        dispStrMLV(EO_X ,EO_Y+8,"Spot already taken", 1);
    }
}

void lifebarMLV(int x, int y, int l) { // La "barre de vie" sera le nombre life en dessous du chips ou du virus
    char ls[5]; sprintf(ls, "%4d", l);
    dispStrMLV(x, y+15, ls, 0);
}

void putSpriteMLV(int x, int y, int s, int l) {
    int px = (s % 5)*16; int py = (s / 5)*16; // les coordonnées du sprite dans sprites.png
    MLV_draw_partial_image( assets.sprites.sp , px,py,16,16 , x , y );
    if(l != NOLIFE) lifebarMLV(x, y, l); // Si l = -1 alors on ne l'affiche pas
}

void dispGridMLV(Game * game) {
    Chips * C = game->chips;
    Virus * V = game->virus;
    for(int i=0; i<7; i++) { // 7 lignes bleues pour symboliser les lines
        MLV_draw_filled_rectangle(0, GO_Y+7+i*24, WIDTH, 2, assets.colors.ln);
        for(int j=0; j<24; j++) {
            MLV_draw_filled_rectangle((GO_X+5+j*24), (GO_Y+5+i*24), 6, 6, assets.colors.ln);
        }
    }
    while(C != NULL) { // On affiche les chips
        int x = C->position-1, y = C->line-1;
        putSpriteMLV(GO_X+x*24, GO_Y+y*24, getChipsIndexFromType(C->type), C->life);
        C = C->next;
    }
    while(V != NULL) { // On affiche les virus
        if(V->position != OOB) {
        int x = V->position-1, y = V->line-1;
        putSpriteMLV(GO_X+x*24, GO_Y+y*24, getVirusIndexFromType(V->type)+5, V->life);
        }
        V = V->next;
    }
}

void dispMarketMLV() {
    char info[32];
    dispStrMLV(MO_X+24, MO_Y-24, "Name     Price Power Life", 1);
    for(int i=0; i<TABCHIPS_LEN; i++) { // Les différents chips, ligne par ligne, avec leurs icônes
        char  * nom = table_of_chips[i].nom;
        Chips * chp = &(table_of_chips[i].chips);
        putSpriteMLV(MO_X, (MO_Y+i*24), i, NOLIFE);
        sprintf(info, 
            "%-8s $%4d %5d %4d", 
            nom, chp->price, chp->power, chp->life
        );
        dispStrMLV(MO_X+24, MO_Y+i*24, info, 1);
    }
    dispStrMLV(MO_X+24, MO_Y+5*24, "Finish", 1);
}

void dispUpcomingWaveMLV(Virus * VL) {
    dispStrMLV(VO_X, VO_Y, "A wave of viruses are approaching...", 1);
    while (VL != NULL) {
        int x = VO_X + VL->turn * 24;
        int y = VO_Y + VL->line * 24;
        int s = getVirusIndexFromType(VL->type) + 5;
        putSpriteMLV(x, y, s, NOLIFE);
        VL = VL->next;
    }
}

// Cette fonction sert à avoir une boite d'information à coté de la souris
int showInfosMLV(int x, int y, InfoType type, void * data) {
    char * nom; int life, power;
    Chips * chp = NULL; Virus * vrs = NULL; int * datint; char * str;
    switch (type) {
    case SPRITE: // Quand la souris transporte un Chips (pour la partie achat)
        datint = (int*)data;
        putSpriteMLV(x+16, y+16, *datint, NOLIFE);
        return 1;
    case CHIPS: // Quand la souris pointe un Chips sur la grille
        chp = (Chips*)data;
        nom = getChipsFromType(chp->type)->nom;
        life = chp->life; power = chp->power;
        break;
    case VIRUS: // Quand la souris pointe un Virus sur la grille ou sur la vague à venir
        vrs = (Virus*)data;
        nom = getVirusFromType(vrs->type)->nom;
        life = vrs->life; power = vrs->power;
        break;
    case DEBUG:
        str = (char*)data;
        dispStrMLV(x+16, y+16, str, 1);
        return 1;
    default: case NONE: // Quand rien du tout
        return 0;
    }
    MLV_draw_rectangle(x+16, y-48, 88, 48, assets.colors.bd);
    MLV_draw_filled_rectangle(x+16, y-48, 88, 48, assets.colors.bx);
    dispStrMLV(x+24, y-40, nom, 1);
    dispIntMLV(x+24, y-24, "Life:  ", life , 1);
    dispIntMLV(x+24, y-16, "Power: ", power, 1);
    return 1;
}

int msgBoxMLV(char ** input , char* str , int prompt) {
    int size_w = 0, size_h = 1, count = 0; char * str_c = str;
    while(*str_c) {
        if(*str_c == '\n') {
            count = 0;
            size_h++;
        } else {
            if(count > size_w) {
                size_w = count;
            }
            count++;
        }
        str_c++;
    }
    MLV_draw_text_box_with_font(
        WIDTH/2-32-8*size_w/2, HEIGTH/2-32-8*size_h/2, size_w*8+64, size_h*8+64,
        str, assets.fonts.ma, 12,
        assets.colors.bd, assets.colors.tx, assets.colors.bx,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_TOP
    );
    switch (prompt) {
    case 0: default:
        dispStrMLV(WIDTH/2 - 8, HEIGTH/2 +size_h*8+8 , "Ok", 1);
        break;
    case 1:
        dispStrMLV(WIDTH/2 - 72, HEIGTH/2 +size_h*8+8 , "Yes", 1);
        dispStrMLV(WIDTH/2 + 56, HEIGTH/2 +size_h*8+8 , "No", 1);
        break;
    case 2:
        MLV_update_window();
        MLV_wait_input_box_with_font(
            WIDTH/4, HEIGTH/2 +size_h*8+8, WIDTH/2, 32,
            assets.colors.bd, assets.colors.tx, assets.colors.bx,
            "", input, assets.fonts.ma
        );
        return 1;
    }
    int mx, my, pointing;
    char mb;
    while(1) {
        fetchMousePositionMLV(&mx, &my, &mb);
        switch (prompt) {
        case 0: default:
            if( mx > WIDTH/2 - 20 && mx < WIDTH/2 + 20 && my > HEIGTH/2 + size_h*8-4 && my < HEIGTH/2 + size_h*8+24 ) {
                pointing = 2;
            }
            else {
                pointing = 0;
            }
            break;
        case 1:
            if( mx > WIDTH/2 - 84 && mx < WIDTH/2 - 50 && my > HEIGTH/2 + size_h*8-4 && my < HEIGTH/2 + size_h*8+24 ) {
                pointing = 2;
            }
            else if( mx > WIDTH/2 + 44 && mx < WIDTH/2 + 82 && my > HEIGTH/2 + size_h*8-4 && my < HEIGTH/2 + size_h*8+24 ) {
                pointing = 1;
            }
            else {
                pointing = 0;
            }
            break;
        }
        if(mb & 1) {
            if(pointing > 0) return pointing-1;
        }
        MLV_update_window();
        MLV_wait_milliseconds(1000/24);
    }
    return 0;
}

void fetchMousePositionMLV(int * x, int * y, char * buttons) {
    MLV_get_mouse_position(x, y);
    *buttons = 0;
    *buttons += (MLV_get_mouse_button_state(MLV_BUTTON_LEFT  ) == MLV_PRESSED) << 0;
    *buttons += (MLV_get_mouse_button_state(MLV_BUTTON_MIDDLE) == MLV_PRESSED) << 1;
    *buttons += (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT ) == MLV_PRESSED) << 2;
}

int getGridPositionFromMouseMLV(int * l, int * p, int x, int y) {
    if(
        x > GO_X - 4 && x < GO_X - 4 + 24*24 &&
        y > GO_Y - 4 && y < GO_Y - 4 +  7*24
    ) {
        *p = (x+4-GO_X)/24 +1;
        *l = (y+4-GO_Y)/24 +1;
        return 1;
    } return 0;
}

int getChipsIndexOnMarketFromMouseMLV(int * i, int x, int y) {
    if(
        x > MO_X - 4 && x < MO_X - 4 + 8*24 &&
        y > MO_Y - 4 && y < MO_Y - 4 + 24*6
    ) {
        *i = (y+4-MO_Y)/24;
        return 1;
    } return 0;
}

Virus * getVirusOnWaveFromMouseMLV(Virus * VL, int x, int y) {
    if(
        x > VO_X - 4 && x < VO_X - 4 + 24*12 &&
        y > VO_Y - 4 && y < VO_Y - 4 + 24*8
    ) {
        int p = (x+4-VO_X)/24 +1;
        int l = (y+4-VO_Y)/24 +1;
        while(VL != NULL) {
            if(VL->line == l-1 && VL->turn == p-1) {
                return VL;
            }
            VL = VL->next;
        }
        return NULL;
    } return NULL;
}
