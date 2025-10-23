#pragma once

#ifndef STAN_H  
#define STAN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//Klasa Ruchy zawiera metody dla:
// sprawdzania mo¿liwych ruchów dla podanego gracza,
// odwracanie pionków przeciwnika zgodnie z zasadami gry Reversi.
class Ruchy {
public:
    void mozliwosc_ruchu(char plansza[8][8], int* tak_nie, char znak_gracza, char znak_przeciwnika);
    void zmiana_znakow(char plansza[8][8], char znak_gracza, char znak_przeciwnika, int i_poz, int j_poz);
};

#endif