#pragma once

#ifndef GRACZ_H  
#define GRACZ_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Abstrakcyjna klasa bazowa dla graczy.
// Przechowuje symbol gracza i definiuje interfejs ruchu.
// Klasy dziedzicz¹ce (GraczCzlowiek, Robot) musz¹ zaimplementowaæ metodê wykonajRuch.
class Gracz {
protected:
    char symbol;

public:
    Gracz(char s) : symbol(s) {}
    virtual ~Gracz() = default;

    virtual char getSymbol() const { return symbol; }
    virtual void wykonajRuch(char plansza[8][8], int* x, int* y) = 0;
};
#endif