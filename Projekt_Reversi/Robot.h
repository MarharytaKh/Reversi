#pragma once

#ifndef ROBOT_H  
#define ROBOT_H

#include <iostream>
#include "Gracz.h"
// Klasa Robot dziedziczy po klasie Gracz.
// Reprezentuje gracza kompuerowego, automatycznego (robota).
class Robot : public Gracz {
public:
    Robot(char s);
    void wykonajRuch(char plansza[8][8], int* x, int* y) override;

private:
    void wybierzLepszyRuch(char plansza[8][8], char znak_robota, char znak_gracza, int* x, int* y);
};

#endif

