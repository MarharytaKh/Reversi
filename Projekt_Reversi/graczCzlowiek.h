#pragma once
#include "Gracz.h"
#include <iostream>

#ifndef CZLOWIEK_H  
#define CZLOWIEK_H
// Klasa GraczCzlowiek dziedziczy po klasie Gracz.
// Reprezentuje gracza sterowanego przez u¿ytkownika (cz³owieka).
class GraczCzlowiek : public Gracz {
public:
    GraczCzlowiek(char s);
    void wykonajRuch(char plansza[8][8], int* x, int* y) override;
};

#endif