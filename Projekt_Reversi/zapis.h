#pragma once

#ifndef ZAPISYWANIE_H  
#define ZAPISYWANIE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Klasa Zapis odpowiedzialna jest za przetwarzanie i aktualizacjê statystyk graczy.
// Umo¿liwia zapisanie wyniku do pliku "records.txt", obliczanie rankingu oraz sortowanie graczy
// wed³ug skutecznoœci (procent wygranych malej¹co).
class Zapis {
private:
	char nazwaPliku[35];
public:
	void wczytywanie_z_pliku(char nick[30], int w_p);
	void najlepsi_graczy();
	void ranking_tego_graczy(char nick[30]);
};

#endif