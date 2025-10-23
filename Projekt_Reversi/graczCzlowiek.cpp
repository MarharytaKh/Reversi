#include "GraczCzlowiek.h"
// Konstruktor klasy GraczCzlowiek.
// s -Symbol gracza (np. 'X' lub 'O').
GraczCzlowiek::GraczCzlowiek(char s) : Gracz(s) {}

// Metoda nadpisuje metodę czysto wirtualną wykonajRuch z klasy Gracz.
// Pobiera od użytkownika współrzędne pola (litera i cyfra), na które chce postawić pionek.
// Weryfikuje poprawność danych — litera A–H i liczba 1–8.
// W przypadku błędu, prosi użytkownika o ponowne wprowadzenie ruchu.
// Jeśli dane są poprawne, zapisuje współrzędne i, jeśli wybrane miejsce odpowiada zasadom Reversi, aktualizuje planszę.
// 
// Parametry:
// plansza -Tablica 8x8 reprezentująca aktualny stan planszy.
// x       -Wskaźnik na zmienną typu int, do której zostanie wpisany wiersz wybranego pola.
// y       -Wskaźnik na zmienną typu int, do której zostanie wpisana kolumna wybranego pola.
void GraczCzlowiek::wykonajRuch(char plansza[8][8], int* x, int* y) {
    int rzad;
    char kolumna;
    int proba = 1; // Flaga sterująca pętlą – dopóki ruch jest niepoprawny, użytkownik będzie proszony o ponowny input

    std::cout << "\nGracz " << symbol << ", podaj ruch (np. D3): ";
    while (proba) {
        std::cin >> kolumna >> rzad;

        if (std::cin.fail()) {
            // Jeśli wystąpił błąd wejścia (np. litera zamiast liczby), czyszczy strumień i prosi o ponowny input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Nieprawidlowy ruch, sprobuj ponownie.\n";
        }
        else {
            // Sprawdzenie, czy użytkownik nie wpisał zbyt wielu znaków (np. D375fg)
            char pozostale = std::cin.peek();
            if (pozostale != '\n') {
                std::cin.ignore(1000, '\n');
                std::cout << "Nieprawidlowy ruch, sprobuj ponownie.\n";
            }
            else {
                kolumna = std::toupper(kolumna); //Zamiana litery na wielką
                // Sprawdzenie, czy dane mieszczą się w zakresie planszy (A–H, 1–8)
                if ((kolumna < 'A' || kolumna>'H') || (rzad < 1 || rzad>8)) {
                    std::cin.ignore(1000, '\n');
                    std::cout << "Nieprawidlowy ruch, sprobuj ponownie.\n";
                }
                else {
                    // Przekształcenie danych wejściowych na indeksy tablicy (0–7)
                    *x = rzad - 1;
                    *y = kolumna - 'A';

                    // Sprawdzenie, czy na wybranym pole można wykonać ruch i wstawenie symbolu gracza jeśli można
                    if (plansza[*x][*y] == '-') {
                        plansza[*x][*y] = symbol;
                        proba = 0;
                    }
                    else {
                        std::cout << "Nieprawidlowy ruch, sprobuj ponownie.\n";
                    }
                    // Wyczyszczenie dodatkowego input
                    std::cin.ignore(1000, '\n');
                }
            }
            
        }

    }
}