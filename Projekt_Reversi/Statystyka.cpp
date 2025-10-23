#include "statystyka.h"
// Metoda klasy Statystyka oblicza aktualn¹ liczbê pionków dwóch graczy na planszy.
//
// Parametry:
// plansza      -tablica 8x8 reprezentuj¹ca aktualny stan gry;
// znak_gracza  -znak reprezentuj¹cy pionki pierwszego gracza (np. 'X' lub 'O');
// znak_gracza2 -znak reprezentuj¹cy pionki drugiego gracza (np. 'X' lub 'O');
// ilosc_gracz1 -wskaŸnik na zmienn¹ typu int, do której zostanie zapisana liczba pionków pierwszego gracza;
// ilosc_gracz2 -wskaŸnik na zmienn¹ typu int, do której zostanie zapisana liczba pionków drugiego gracza.
void Statystyka::obliczenie_aktualnej_ilosci_znakow(char plansza[8][8],char znak_gracza, char znak_gracza2, int* ilosc_gracz1, int* ilosc_gracz2) {
	*ilosc_gracz1 = 0;
	*ilosc_gracz2 = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (plansza[i][j] == znak_gracza) {
				(*ilosc_gracz1)++;
			}
			else if (plansza[i][j] == znak_gracza2) {
				(*ilosc_gracz2)++;
			}
		}
	}
}
// Metoda klasy Statystyka wypisuje liczbê pionków pierwszego gracza.
void Statystyka::wypisz_pierwszego_gracza() {
	std::cout << ilosc_gracz1;
}
// Metoda klasy Statystyka wypisuje liczbê pionków drugiego gracza.
void Statystyka::wypisz_drugiego_gracza() {
	std::cout << ilosc_gracz2;
}