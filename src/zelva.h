#pragma once

#include <stdbool.h>

typedef struct pos_t {
    double X;
    double Y;
}pos_t;

//return current position to pos_t
pos_t XY_pos();

// inicializacni funkce
bool zelva_init();

// ukoncovaci funkce
void zelva_quit();

// vycisteni piskoviste, navrat na puvodni pozici (0, 0) a otoceni na puvodni smer (doprava)
void zelva_reset();

// nastaveni barvy stopy
void zelva_color(unsigned char red, unsigned char green, unsigned char blue);

// pochod dopredu o zadanou vzdalenost (v pixelech)
void dopredu(double vzdalenost);

// pochod dozadu o zadanou vzdalenost (v pixelech)
void dozadu(double vzdalenost);

// otoceni doleva o zadany uhel (ve stupnich)
void doleva(double uhel);

// otoceni doprava o zadany uhel (ve stupnich)
void doprava(double uhel);

// ceka zadany pocet sekund pred pokracovanim programu
void sleep(double t);

//kreslení neviditelně
void dopredu_bezkresleni(double vzdalenost);
