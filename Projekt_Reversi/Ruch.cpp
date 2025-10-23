#include "Ruch.h"
#include <iostream>

// Metoda sprawdza wszystkie pola na planszy, na które gracz zgodnie z zasadami gry może postawić swój pionek.
// Sprawdza wszystkie 8 kierunków.
// Oznacza dostepne do wybora pola znakiem '-'.
// Jeśli jakikolwiek ruch jest możliwy, ustawia *tak_nie na 1.
//
// Parametry:
// plansza          -Tablica 8x8 reprezentująca aktualny stan planszy gry.
// tak_nie          -Wskaźnik na zmienną typu int; zostanie ustawiona na 1, jeśli jakikolwiek ruch jest możliwy.
// znak_gracza      -Znak reprezentujący bieżącego gracza (np. 'X' lub 'O'), dla ktorego funkcja sprawdza mozliwości ruchu.
// znak_przeciwnika -Znak reprezentujący przeciwnika.

void Ruchy::mozliwosc_ruchu(char plansza[8][8], int* tak_nie, char znak_gracza, char znak_przeciwnika) {
    int p = 0, l = 0, d = 0, g = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
            // prawo
            if (j + 1 < 8 && plansza[i][j + 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                for (int prawo = j + 1; prawo < 8 && plansza[i][prawo] == znak_przeciwnika; prawo++) {
                    p = prawo;
                }
                if (p + 1 < 8 && plansza[i][p + 1] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            // lewo
            if (j - 1 >= 0 && plansza[i][j - 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                for (int lewo = j - 1; lewo >= 0 && plansza[i][lewo] == znak_przeciwnika; lewo--) {
                    l = lewo;
                }
                if (l - 1 >= 0 && plansza[i][l - 1] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            // dól
            if (i + 1 < 8 && plansza[i + 1][j] == znak_przeciwnika && plansza[i][j] == ' ') {
                for (int dol = i + 1; dol < 8 && plansza[dol][j] == znak_przeciwnika; dol++) {
                    d = dol;
                }
                if (d + 1 < 8 && plansza[d + 1][j] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            // góra
            if (i - 1 >= 0 && plansza[i - 1][j] == znak_przeciwnika && plansza[i][j] == ' ') {
                for (int gora = i - 1; gora >= 0 && plansza[gora][j] == znak_przeciwnika; gora--) {
                    g = gora;
                }
                if (g - 1 >= 0 && plansza[g - 1][j] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            //prawy gorny kąt
            if (i - 1 >= 0 && j + 1 < 8 && plansza[i - 1][j + 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                int x = i - 1;
                int y = j + 1;
                while (x >= 0 && y < 8 && plansza[x][y] == znak_przeciwnika) {
                    x--;
                    y++;
                }
                if (x >= 0 && y < 8 && plansza[x][y] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }
            // prawy dolny kąt
            if (i + 1 < 8 && j + 1 < 8 && plansza[i + 1][j + 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                int x = i + 1;
                int y = j + 1;
                while (x < 8 && y < 8 && plansza[x][y] == znak_przeciwnika) {
                    x++;
                    y++;
                }
                if (x < 8 && y < 8 && plansza[x][y] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            // lewy dolny kąt
            if (i + 1 < 8 && j - 1 >= 0 && plansza[i + 1][j - 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                int x = i + 1;
                int y = j - 1;
                while (x < 8 && y >= 0 && plansza[x][y] == znak_przeciwnika) {
                    x++;
                    y--;
                }
                if (x < 8 && y >= 0 && plansza[x][y] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }

            // lewy górny kąt
            if (i - 1 >= 0 && j - 1 >= 0 && plansza[i - 1][j - 1] == znak_przeciwnika && plansza[i][j] == ' ') {
                int x = i - 1;
                int y = j - 1;
                while (x >= 0 && y >= 0 && plansza[x][y] == znak_przeciwnika) {
                    x--;
                    y--;
                }
                if (x >= 0 && y >= 0 && plansza[x][y] == znak_gracza) {
                    *tak_nie = 1;
                    plansza[i][j] = '-';
                }
            }
        }
    }
}
// Metoda zmienia pionki przeciwnika na pionki gracza po wykonaniu ruchu.
// Działa względem nowo postawionego pionka, sprawdzając wszystkie 8 kierunków.
// 
// Parametry:
// plansza          -Tablica 8x8 reprezentująca aktualny stan planszy.
// znak_gracza      -Znak gracza (np. 'X' lub 'O'), który wykonał ruch.
// znak_przeciwnika -Znak przeciwnika (np. 'X' lub 'O').
// i_poz            -Wiersz pola, które gracz wybral wcześniej.
// j_poz            -Kolumna pola, które gracz wybral wcześniej.

void Ruchy::zmiana_znakow(char plansza[8][8], char znak_gracza, char znak_przeciwnika, int i_poz, int j_poz) {

    int kierunki[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1},{-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

    for (int k = 0; k < 8; k++) {
        int wiersz_kierunek = kierunki[k][0];
        int kolumna_kierunek = kierunki[k][1];
        int x = i_poz + wiersz_kierunek;
        int y = j_poz + kolumna_kierunek;
        int czy_jest_przeciwnik = 0;

        while (x >= 0 && x < 8 && y >= 0 && y < 8 && plansza[x][y] == znak_przeciwnika) {
            x += wiersz_kierunek;
            y += kolumna_kierunek;
            czy_jest_przeciwnik = 1;
        }

        if (czy_jest_przeciwnik && x >= 0 && x < 8 && y >= 0 && y < 8 && plansza[x][y] == znak_gracza) {
            int zam_x = i_poz + wiersz_kierunek;
            int zam_y = j_poz + kolumna_kierunek;
            while (zam_x != x || zam_y != y) {

                if (!(zam_x < 0 || zam_x >= 8 || zam_y < 0 || zam_y >= 8)) {
                    plansza[zam_x][zam_y] = znak_gracza;
                    zam_x += wiersz_kierunek;
                    zam_y += kolumna_kierunek;
                }
            }
        }
    }
}

