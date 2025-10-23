#define _CRT_SECURE_NO_WARNINGS
#include "zapis.h"
#include <fstream>
#include <cstdio>
#include <cstring>

#define MAX_GRACZY 50
// Struktura przechowuj¹ca dane statystyczne pojedynczego gracza
struct GraczStatystyka {
    char nick[50]; // imie (nazwa) gracza;
    int wygrane;      // iloœæ wygranych gier;
    int przegrane;    // iloœæ przegranych gier;
    int procent;   //procent wygranych gier od wszystkich (wygrane+przegrane).
};

// Metoda klasy Zapis, która wczytuje dane z pliku "records.txt", lub tworzy taki, jeœli jego nie istnieje
// Aktualizuje statystyki gracza, lub, jeœli nie ma go w pliku, tworzy nowy zapis.
// Sortuje listê rekordów wzglêdem procenta (malej¹co) i zapisuje zaktualizowane dane z powrotem do pliku.
//
// Parametry:
// nick –nazwa gracza, którego statystyki maj¹ zostaæ zaktualizowane;
// w_p  –wynik gry dla gracza: 1 oznacza zwyciêstwo, 0 oznacza przegran¹.
void Zapis::wczytywanie_z_pliku(char nick[30], int w_p) {
    GraczStatystyka gracze[MAX_GRACZY];
    FILE* plik = fopen("records.txt", "r");

    // Jeœli plik nie istnieje –jest tworzony nowy z pierwszym wpisem;
    if (plik == NULL) {
        plik = fopen("records.txt", "w");
        if (plik != NULL) {
            if (w_p == 1)
                fprintf(plik, "%s  %d  %d  %d\n", nick, 1, 0, 100);
            else
                fprintf(plik, "%s  %d  %d  %d\n", nick, 0, 1, 0);
            fclose(plik);
        }
        return;
    }

    // Wczytanie danych z pliku
    int ilosc_graczy = 0;
    while (ilosc_graczy < MAX_GRACZY &&
        fscanf(plik, "%49s %d %d %d", gracze[ilosc_graczy].nick, &gracze[ilosc_graczy].wygrane, &gracze[ilosc_graczy].przegrane, &gracze[ilosc_graczy].procent) == 4) {

        if (gracze[ilosc_graczy].wygrane < 0 || gracze[ilosc_graczy].przegrane < 0) {
            continue;
        }
        // Obliczenie procentu wygranych (na wypadek b³êdnych liczb w pliku)
        int suma = gracze[ilosc_graczy].wygrane + gracze[ilosc_graczy].przegrane;
        gracze[ilosc_graczy].procent = (suma > 0) ? (gracze[ilosc_graczy].wygrane * 100) / suma : 0;

        ilosc_graczy++;
    }
    fclose(plik);

    // Sprawdzenie, czy gracz (nick) ju¿ istnieje
    int istnieje_taki_nick = 0;
    for (int i = 0; i < ilosc_graczy; i++) {
        if (strcmp(gracze[i].nick, nick) == 0) {
            if (w_p == 1)
                gracze[i].wygrane++;
            else
                gracze[i].przegrane++;

            int suma = gracze[i].wygrane + gracze[i].przegrane;
            gracze[i].procent = suma > 0 ? (gracze[i].wygrane * 100) / suma : 0;
            istnieje_taki_nick = 1;
            break;
        }
    }

    // Jeœli gracza nie istnieje w pliku –metoda go dodaje
    if (!istnieje_taki_nick && ilosc_graczy < MAX_GRACZY) {
        strcpy(gracze[ilosc_graczy].nick, nick);
        gracze[ilosc_graczy].wygrane = (w_p == 1) ? 1 : 0;
        gracze[ilosc_graczy].przegrane = (w_p == 0) ? 1 : 0;
        gracze[ilosc_graczy].procent = (w_p == 1) ? 100 : 0;
        ilosc_graczy++;
    }
    //sortowanie wzglêdem procenta
    for (int i = 0; i < ilosc_graczy - 1; i++) {
        for (int j = 0; j < ilosc_graczy - i - 1; j++) {
            if (gracze[j].procent < gracze[j + 1].procent) {
                GraczStatystyka temp = gracze[j];
                gracze[j] = gracze[j + 1];
                gracze[j + 1] = temp;
            }
        }
    }
    // Nadpisanie pliku nowymi danymi
    plik = fopen("records.txt", "w");
    if (plik != NULL) {
        for (int i = 0; i < ilosc_graczy; i++) {
            fprintf(plik, "%s  %d  %d  %d\n", gracze[i].nick,
                gracze[i].wygrane,
                gracze[i].przegrane,
                gracze[i].procent);
        }
        fclose(plik);
    }
}
// Metoda klasy Zapis, która wypisuje ranking (statystyki) wybranego gracza.
//
// Parametry:
// nick –nazwa gracza, którego dane maj¹ byæ wyœwietlone.
void Zapis::ranking_tego_graczy(char nick[30]) {
    FILE* plik = fopen("records.txt", "r");
    std::cout << "\n         ^^^^^^^^^^^^^^^ ranking " << nick<<" ^^^^^^^^^^^^^^^\n";
    if (plik) {
        std::cout << "\nnazwa gracza     wygrane    porazki    procent wygranych\n";
        GraczStatystyka g;
        int i = 0;
        while (fscanf(plik, "%s %d %d %d", g.nick, &g.wygrane, &g.przegrane, &g.procent) == 4) {
            if (strcmp(g.nick, nick) == 0) {
                printf("%-18s %-9d %-10d %d %%\n", g.nick, g.wygrane, g.przegrane, g.procent);
            }
        }
        fclose(plik);
    }
}
// Metoda klasy Zapis, która wczytuje dane z pliku "records.txt" i
// wypisuje ranking (statystyki) pierwszych piêciu graczy (lepszych wzgledem procenta).
void Zapis::najlepsi_graczy() {
    std::cout << "\n         ~~~~~~~~~~~~~~~ Top 5 strategow ~~~~~~~~~~~~~~~\n";
    FILE* plik = fopen("records.txt", "r");
    if (plik) {
        std::cout << "\nmiejsce  nazwa gracza     wygrane    porazki    procent wygranych\n";
        GraczStatystyka g;
        int i = 0;
        while (i < 5 && fscanf(plik, "%s %d %d %d", g.nick, &g.wygrane, &g.przegrane, &g.procent) == 4) {
            printf("%-9d ", i+1);
            printf("%-15s %-11d %-10d %d %%\n", g.nick, g.wygrane, g.przegrane, g.procent);
            i++;
        }

        fclose(plik);
    }
}