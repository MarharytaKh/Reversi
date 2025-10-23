#pragma once

#ifndef STATYSTYKA_H  
#define STATYSTYKA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Klasa Statystyka odpowiedzialna jest za analizê stanu planszy.
// Oblicza aktualne liczby pionków ka¿dego gracza
// oraz wyœwietla te wartoœci na ekranie.
class Statystyka {
private:
	int ilosc_gracz1;
	int ilosc_gracz2;
public:
	void obliczenie_aktualnej_ilosci_znakow(char plansza[8][8], char znak_gracza, char znak_gracza2, int* ilosc_gracz1, int* ilosc_gracz2);
	void wypisz_pierwszego_gracza();
	void wypisz_drugiego_gracza();
};

#endif
