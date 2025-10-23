#include "Robot.h"
#include <cstdlib>
#include <ctime>
// Konstruktor klasy Robot.
// s -Symbol robota (np. 'X' lub 'O').
Robot::Robot(char s) : Gracz(s) {}

// Metoda klasy Robot nadpisuje metodę czysto wirtualną wykonajRuch z klasy Gracz.
// I wywołuje metodę wybierającą najlepszy możliwy ruch robota na planszy.
// 
// Parametry:
// plansza[8][8] -tablica reprezentująca aktualny stan gry;
// x, y          -wskaźniki na zmienne, do których zostaną zapisane współrzędne wybranego ruchu;
void Robot::wykonajRuch(char plansza[8][8], int* x, int* y) {
    wybierzLepszyRuch(plansza, symbol, symbol == 'O' ? 'X' : 'O', x, y);
}
// Metoda klasy Robot wybiera najlepszy możliwy ruch dla robota na podstawie aktualnego stanu planszy.
// Dla każdego pola '-' sprawdza, ile pionków przeciwnika można przejąć w różnych kierunkach.
// Zapamiętuje wszystkie pola, które dają największą możliwą liczbę przejęć.
// Spośród nich losowo wybiera jedno pole i wykonuje na nim ruch.
//
// Parametry:
// plansza      – tablica 8x8 reprezentująca aktualny stan planszy.
// znak_robota  – znak reprezentujący pionek gracza sterowanego przez komputer.
// znak_gracza  – znak reprezentujący pionek przeciwnika (gracza).
// x, y         – wskaźniki na współrzędne pola, na które robot wykona ruch.
void Robot::wybierzLepszyRuch(char plansza[8][8], char znak_robota, char znak_gracza, int* x, int* y) {
    int p = 0, l = 0, d = 0, g = 0;
    int najwiecej_Znakow_Gracza = 0;
    char* najlepsze_miejsce[16] = { NULL };
    int n_m_w = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // prawo
            if (j + 1 < 8 && plansza[i][j + 1] == znak_gracza && plansza[i][j] == '-') {
                for (int prawo = j + 1; prawo < 8 && plansza[i][prawo] == znak_gracza; prawo++) {
                    p = prawo;
                }
                if (p + 1 < 8 && plansza[i][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < p - j) {
                        najwiecej_Znakow_Gracza = p - j;
                    }
                }
            }
            // lewo
            if (j - 1 >= 0 && plansza[i][j - 1] == znak_gracza && plansza[i][j] == '-') {
                for (int lewo = j - 1; lewo >= 0 && plansza[i][lewo] == znak_gracza; lewo--) {
                    l = lewo;
                }
                if (l - 1 >= 0 && plansza[i][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < j - l)
                        najwiecej_Znakow_Gracza = j - l;
                }
            }
            // dól
            if (i + 1 < 8 && plansza[i + 1][j] == znak_gracza && plansza[i][j] == '-') {
                for (int dol = i + 1; dol < 8 && plansza[dol][j] == znak_gracza; dol++) {
                    d = dol;
                }
                if (d + 1 < 8 && plansza[d + 1][j] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < d - i)
                        najwiecej_Znakow_Gracza = d - i;
                }
            }
            // góra
            if (i - 1 >= 0 && plansza[i - 1][j] == znak_gracza && plansza[i][j] == '-') {
                for (int gora = i - 1; gora >= 0 && plansza[gora][j] == znak_gracza; gora--) {
                    g = gora;
                }
                if (g - 1 >= 0 && plansza[g - 1][j] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < i - g)
                        najwiecej_Znakow_Gracza = i - g;
                }
            }
            // prawy dolny kąt
            if (i + 1 < 8 && j + 1 < 8 && plansza[i + 1][j + 1] == znak_gracza && plansza[i][j] == '-') {
                int pd_i = i + 1, pd_j = j + 1;
                while (pd_i < 8 && pd_j < 8 && plansza[pd_i][pd_j] == znak_gracza) {
                    d = pd_i;
                    p = pd_j;
                    pd_i++;
                    pd_j++;
                }
                if (d + 1 < 8 && p + 1 < 8 && plansza[d + 1][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < d - i)
                        najwiecej_Znakow_Gracza = d - i;
                }
            }
            // prawy górny kąt
            if (i - 1 >= 0 && j + 1 < 8 && plansza[i - 1][j + 1] == znak_gracza && plansza[i][j] == '-') {
                int pg_i = i - 1, pg_j = j + 1;
                while (pg_i >= 0 && pg_j < 8 && plansza[pg_i][pg_j] == znak_gracza) {
                    g = pg_i;
                    p = pg_j;
                    pg_i--;
                    pg_j++;
                }
                if (g - 1 >= 0 && p + 1 < 8 && plansza[g - 1][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < i - g)
                        najwiecej_Znakow_Gracza = i - g;
                }
            }
            // lewy dolny kąt
            if (i + 1 < 8 && j - 1 >= 0 && plansza[i + 1][j - 1] == znak_gracza && plansza[i][j] == '-') {
                int ld_i = i + 1, ld_j = j - 1;
                while (ld_i < 8 && ld_j >= 0 && plansza[ld_i][ld_j] == znak_gracza) {
                    d = ld_i;
                    l = ld_j;
                    ld_i++;
                    ld_j--;
                }
                if (d + 1 < 8 && l - 1 >= 0 && plansza[d + 1][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < d - i)
                        najwiecej_Znakow_Gracza = d - i;
                }
            }
            // lewy górny kąt
            if (i - 1 >= 0 && j - 1 >= 0 && plansza[i - 1][j - 1] == znak_gracza && plansza[i][j] == '-') {
                int lg_i = i - 1, lg_j = j - 1;
                while (lg_i >= 0 && lg_j >= 0 && plansza[lg_i][lg_j] == znak_gracza) {
                    g = lg_i;
                    l = lg_j;
                    lg_i--;
                    lg_j--;
                }
                if (g - 1 >= 0 && l - 1 >= 0 && plansza[g - 1][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza < i - g)
                        najwiecej_Znakow_Gracza = i - g;
                }
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // prawo
            if (j + 1 < 8 && plansza[i][j + 1] == znak_gracza && plansza[i][j] == '-') {
                for (int prawo = j + 1; prawo < 8 && plansza[i][prawo] == znak_gracza; prawo++) {
                    p = prawo;
                }
                if (p + 1 < 8 && plansza[i][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == p - j) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // lewo
            if (j - 1 >= 0 && plansza[i][j - 1] == znak_gracza && plansza[i][j] == '-') {
                for (int lewo = j - 1; lewo >= 0 && plansza[i][lewo] == znak_gracza; lewo--) {
                    l = lewo;
                }
                if (l - 1 >= 0 && plansza[i][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == j - l) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // dól
            if (i + 1 < 8 && plansza[i + 1][j] == znak_gracza && plansza[i][j] == '-') {
                for (int dol = i + 1; dol < 8 && plansza[dol][j] == znak_gracza; dol++) {
                    d = dol;
                }
                if (d + 1 < 8 && plansza[d + 1][j] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == d - i) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // góra
            if (i - 1 >= 0 && plansza[i - 1][j] == znak_gracza && plansza[i][j] == '-') {
                for (int gora = i - 1; gora >= 0 && plansza[gora][j] == znak_gracza; gora--) {
                    g = gora;
                }
                if (g - 1 >= 0 && plansza[g - 1][j] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == i - g) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // prawy dolny kąt
            if (i + 1 < 8 && j + 1 < 8 && plansza[i + 1][j + 1] == znak_gracza && plansza[i][j] == '-') {
                int pd_i = i + 1, pd_j = j + 1;
                while (pd_i < 8 && pd_j < 8 && plansza[pd_i][pd_j] == znak_gracza) {
                    d = pd_i;
                    p = pd_j;
                    pd_i++;
                    pd_j++;
                }
                if (d + 1 < 8 && p + 1 < 8 && plansza[d + 1][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == d - i) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // prawy górny kąt
            if (i - 1 >= 0 && j + 1 < 8 && plansza[i - 1][j + 1] == znak_gracza && plansza[i][j] == '-') {
                int pg_i = i - 1, pg_j = j + 1;
                while (pg_i >= 0 && pg_j < 8 && plansza[pg_i][pg_j] == znak_gracza) {
                    g = pg_i;
                    p = pg_j;
                    pg_i--;
                    pg_j++;
                }
                if (g - 1 >= 0 && p + 1 < 8 && plansza[g - 1][p + 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == i - g) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // lewy dolny kąt
            if (i + 1 < 8 && j - 1 >= 0 && plansza[i + 1][j - 1] == znak_gracza && plansza[i][j] == '-') {
                int ld_i = i + 1, ld_j = j - 1;
                while (ld_i < 8 && ld_j >= 0 && plansza[ld_i][ld_j] == znak_gracza) {
                    d = ld_i;
                    l = ld_j;
                    ld_i++;
                    ld_j--;
                }
                if (d + 1 < 8 && l - 1 >= 0 && plansza[d + 1][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == d - i) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
            // lewy górny kąt
            if (i - 1 >= 0 && j - 1 >= 0 && plansza[i - 1][j - 1] == znak_gracza && plansza[i][j] == '-') {
                int lg_i = i - 1, lg_j = j - 1;
                while (lg_i >= 0 && lg_j >= 0 && plansza[lg_i][lg_j] == znak_gracza) {
                    g = lg_i;
                    l = lg_j;
                    lg_i--;
                    lg_j--;
                }
                if (g - 1 >= 0 && l - 1 >= 0 && plansza[g - 1][l - 1] == znak_robota) {
                    if (najwiecej_Znakow_Gracza == i - g) {
                        najlepsze_miejsce[n_m_w] = &plansza[i][j];
                        n_m_w++;
                    }
                }
            }
        }
    }

    if (n_m_w > 0) {
        srand(time(NULL));
        int a = rand() % n_m_w;
        *najlepsze_miejsce[a] = znak_robota;

        int indeks = najlepsze_miejsce[a] - &plansza[0][0];
        *y = indeks % 8;
        *x = indeks / 8;
    }
}
