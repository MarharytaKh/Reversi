#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "graczCzlowiek.h"
#include "Robot.h"
#include "Ruch.h"
#include "statystyka.h"
#include "zapis.h"
// Funkcja ustawia początkowe ustawienie planszy do gry Reversi.
// Wartości ustawione są zgodnie z zasadami gry
//
// Parametry:
// plansza -Dwuwymiarowa tablica typu char 8x8 reprezentująca planszę gry.
void utworzenie_poczatkowej_planszy(char plansza[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 3 && j == 4) { plansza[i][j] = 'O'; }
            else if (i == 4 && j == 3) { plansza[i][j] = 'O'; }
            else if (i == 3 && j == 3) { plansza[i][j] = 'X'; }
            else if (i == 4 && j == 4) { plansza[i][j] = 'X'; }
            else plansza[i][j] = ' ';
        }
    }
}
// Funkcja wypisuje aktualny stan planszy wraz z liczbą pionków obu graczy.
//
// Parametry:
// plansza      -tablica 8x8 reprezentująca aktualny stan gry;
// ilosc_gracz1 -Liczba pionków gracza X;
// ilosc_gracz2 -Liczba pionków gracza O.
void wypisywanie_planszy(char plansza[8][8], int ilosc_gracz1, int ilosc_gracz2) {
	printf("   A    B    C    D    E    F    G    H\n");
	for (int i = 0; i < 8; i++) {
		printf(" -----------------------------------------\n");
		printf("%d|", i + 1);
		for (int j = 0; j < 8; j++) {
			printf(" %c  |", plansza[i][j]);
		}
        printf(" %d", i + 1);
        if (i == 3) {
            printf("        Gracz X:");
            printf("%d", ilosc_gracz1);
        }
        else if (i == 4) {
            printf("        Gracz O:");
            printf("%d", ilosc_gracz2);
        }
        
		printf("\n");
	}
	printf(" -----------------------------------------\n");
    printf("   A    B    C    D    E    F    G    H\n");
}
// Funkcja usuwa możliwe ruchy oznaczone znakiem '-' z planszy 
// (wyszukuje pola z '-' i zastępuje je ' ')
//
// Parametry:
// plansza -tablica 8x8 reprezentująca aktualny stan gry;
void oczysc_mozlowosci(char plansza[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (plansza[i][j]=='-') plansza[i][j] = ' ';
		}
	}
}
// Funkcja sprawdza, czy plansza została całkowicie zapełniona.
//
// Parametry:
// plansza -tablica 8x8 reprezentująca aktualny stan gry;
//
// Return:
// Zwraca 1, jeśli plansza jest w pełni zapełniona, w przeciwnym razie zwraca 0.
int czy_jest_wypelniona(char plansza[8][8]) {
    int czy_jest = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (plansza[i][j] == ' ') {
                czy_jest = 0;
            }
        }
    }
    return czy_jest;
}
// Funkcja main() – główny punkt wejścia programu Reversi.
//
// Funkcja inicjalizuje planszę do gry oraz obsługuje cały przebieg rozgrywki.
// Gracz ma możliwość wyboru trybu gry: gra z drugim człowiekiem lub z komputerem (robotem).
// W zależności od wyboru użytkownika tworzona jest odpowiednia konfiguracja graczy (obiekty klas pochodnych GraczCzlowiek lub Robot).
//
// Główne etapy funkcji:
// 1. Inicjalizacja początkowej planszy i zmiennych.
// 2. Wybór trybu gry (człowiek vs człowiek lub człowiek vs komputer).
// 3. Utworzenie odpowiednich obiektów graczy i wczytanie nicków.
// 4. Główna pętla gry, która:
//    - oblicza możliwe ruchy dla gracza,
//    - wyświetla planszę,
//    - umożliwia wykonanie ruchu,
//    - aktualizuje planszę,
//    - powtarza kroki dla drugiego gracza lub robota,
//    - sprawdza zakończenie gry (brak możliwych ruchów lub pełna plansza).
// 5. Po zakończeniu rozgrywki:
//    - ogłoszenie zwycięzcy lub remisu,
//    - zapis wyników do pliku,
//    - wyświetlenie rankingu gracza/graczy oraz najlepszych wyników ogólnych.
int main() {
    char plansza[8][8];
    int tak_nie = 1; // Flaga określająca, czy możliwy jest ruch dla któregoś gracza
    int czy_wypelniona = 0; // Zmienna pomocnicza – czy plansza została w całości wypełniona

    int ilosc_gracz1 = 0, ilosc_gracz2 = 0;
    int x_poz = 0, y_poz = 0; // Pozycja ruchu (wiersz, kolumna)
    char nick_1[30]; char nick_2[30];

    char typ_gracza[20]; // Zmienna określająca typ rozgrywki (z graczem lub komputerem)

    utworzenie_poczatkowej_planszy(plansza);
    
    std::cout << "\nWitam w grze Reversi!\n";
    std::cout << "Prosze na poczatek wybrac, chcesz grac z... \n1) kims \n2) komputerem \n";
    
    // Pętla sprawdzająca poprawność wprowadzonego typu gry
    int nie_l = 1;
    while (nie_l) {
        std::cin >> typ_gracza;
        if ((typ_gracza[0] == '1' || typ_gracza[0] == '2') && typ_gracza[1] == '\0') {
            nie_l = 0;
        }
        else {
            std::cout << "\nProsze podac 1 lub 2\n";
        }
    }
    Ruchy ruch;
    Statystyka s;
    Zapis z;
    if (typ_gracza[0] == '1') {
        // Tryb gry: człowiek vs człowiek
        Gracz* gracz1 = new GraczCzlowiek('X');
        Gracz* gracz2 = new GraczCzlowiek('O');
        
        std::cout << "\nGracz X, podaj swoj nickname (bez spacji)\n";
        std::cin >> nick_1;
        std::cout << "\nGracz O, podaj swoj nickname (bez spacji)\n";
        std::cin >> nick_2;

        // Sprawdzenie dostępności ruchów i oczyszczenie planszy z wcześniejszych znaczników
        ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz1->getSymbol(), gracz2->getSymbol());
        oczysc_mozlowosci(plansza);

        std::cout << "GRAMY!\n";
        while (tak_nie && !czy_jest_wypelniona(plansza)) {
            tak_nie = 0;

            // Gracz 1
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz1->getSymbol(), gracz2->getSymbol());

            s.obliczenie_aktualnej_ilosci_znakow(plansza, gracz1->getSymbol(), gracz2->getSymbol(), &ilosc_gracz1, &ilosc_gracz2);
            wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);

            if (tak_nie==1) {
                gracz1->wykonajRuch(plansza, &x_poz, &y_poz);
                ruch.zmiana_znakow(plansza, gracz1->getSymbol(), gracz2->getSymbol(), x_poz, y_poz);
                oczysc_mozlowosci(plansza);
            }
            else if (tak_nie == 0) {
                printf("\nNie masz teraz mozliwosci zrobic ruch\n");
            }
            
            // Gracz 2
            tak_nie = 0;
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz2->getSymbol(), gracz1->getSymbol());


            s.obliczenie_aktualnej_ilosci_znakow(plansza, gracz1->getSymbol(), gracz2->getSymbol(), &ilosc_gracz1, &ilosc_gracz2);
            wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);

            if (tak_nie==1) {
                gracz2->wykonajRuch(plansza, &x_poz, &y_poz);
                ruch.zmiana_znakow(plansza, gracz2->getSymbol(), gracz1->getSymbol(), x_poz, y_poz);
                oczysc_mozlowosci(plansza);
            }
            else if(tak_nie==0){
                printf("\nNie masz teraz mozliwosci zrobic ruch\n");
            }
            // Sprawdzenie czy którykolwiek gracz ma jeszcze ruch
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz1->getSymbol(), gracz2->getSymbol());
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz2->getSymbol(), gracz1->getSymbol());
            oczysc_mozlowosci(plansza);
            if (tak_nie == 0) {
                printf("\nGraczy nie maja mozliwosci zrobic ruch-koniec gry\n");
            }
        }
        wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);
        if (czy_jest_wypelniona(plansza)) {
            // Ogłoszenie zwycięzcy lub remisu i aktualizacja rankingu
            if (ilosc_gracz1 > ilosc_gracz2) {
                std::cout << "\n```````````````````````````````````````````\n";
                std::cout << "Gratulacje za wygrana, " << nick_1<<" (gracz X)";
                std::cout << "\n...........................................\n";
                z.wczytywanie_z_pliku(nick_1, 1);
                z.wczytywanie_z_pliku(nick_2, 0);
            }
            else if (ilosc_gracz2 > ilosc_gracz1) {
                std::cout << "\n```````````````````````````````````````````\n";
                std::cout << "Gratulacje za wygrana, " << nick_2<<" (gracz O)";
                std::cout << "\n...........................................\n";
                z.wczytywanie_z_pliku(nick_2, 1);
                z.wczytywanie_z_pliku(nick_1, 0);
            }
            else if (ilosc_gracz1 == ilosc_gracz2) {
                std::cout << "\nObie strony maja dokladnie tyle samo pionkow. \nNikt nie wygral, ale tez nikt nie przegral – remis!";
            }
        }
        std::cout << "\nKONIEC GRY!\n";
        // Wyświetlenie rankingu graczy
        z.ranking_tego_graczy(nick_1);
        z.ranking_tego_graczy(nick_2);
        // Wyświetlenie rankingu 5 najlepszych graczy
        z.najlepsi_graczy();
        delete gracz1;
        delete gracz2;
    }
    else if (typ_gracza[0] == '2') {
        // Tryb gry: człowiek vs komputer
        Gracz* gracz1 = new GraczCzlowiek('X');
        Gracz* robot = new Robot('O');

        std::cout << "\nGracz X, podaj swoj nickname\n";
        std::cin >> nick_1;

        std::cout << "\nGRAMY!\n";
        while (tak_nie && !czy_jest_wypelniona(plansza)) {
            tak_nie = 0;

            // Gracz człowiek
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz1->getSymbol(), robot->getSymbol());

            s.obliczenie_aktualnej_ilosci_znakow(plansza, gracz1->getSymbol(), robot->getSymbol(), &ilosc_gracz1, &ilosc_gracz2);
            wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);

            if (tak_nie) {
                gracz1->wykonajRuch(plansza, &x_poz, &y_poz);
                ruch.zmiana_znakow(plansza, gracz1->getSymbol(), robot->getSymbol(), x_poz, y_poz);
                oczysc_mozlowosci(plansza);
            }
            else {
                printf("\nNie masz teraz mozliwosci zrobic ruch\n");
            }
            
            tak_nie = 0;
            // Gracz komputer
            ruch.mozliwosc_ruchu(plansza, &tak_nie, robot->getSymbol(), gracz1->getSymbol());

            s.obliczenie_aktualnej_ilosci_znakow(plansza, gracz1->getSymbol(), robot->getSymbol(), &ilosc_gracz1, &ilosc_gracz2);
            
            wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);
            printf("\n");

            if (tak_nie) {
                robot->wykonajRuch(plansza, &x_poz, &y_poz);
                printf("Robot wybiera miejsce: %c%d\n", 'A' + y_poz, x_poz + 1);
                ruch.zmiana_znakow(plansza, robot->getSymbol(), gracz1->getSymbol(), x_poz, y_poz);
                oczysc_mozlowosci(plansza);
            }
            else {
                printf("\nRobot pasuje – brak mozliwosci ruchu.\n");
            }
            // Sprawdzenie czy którykolwiek gracz ma jeszcze ruch
            ruch.mozliwosc_ruchu(plansza, &tak_nie, gracz1->getSymbol(), robot->getSymbol());
            ruch.mozliwosc_ruchu(plansza, &tak_nie, robot->getSymbol(), gracz1->getSymbol());
            if (tak_nie == 0) {
                printf("\nTy i komputer nie macie mozliwosci zrobic ruch-koniec gry\n");
            }
            oczysc_mozlowosci(plansza);
        }

        wypisywanie_planszy(plansza, ilosc_gracz1, ilosc_gracz2);
        if (czy_jest_wypelniona(plansza)) {
            // Ogłoszenie zwycięzcy lub remisu i aktualizacja rankingu
            if (ilosc_gracz1 > ilosc_gracz2) {
                std::cout << "\n```````````````````````````````````````````\n";
                std::cout << "Gratulacje za wygrana, " << nick_1<<" (gracz X)";
                std::cout << "\n...........................................\n";
                z.wczytywanie_z_pliku(nick_1, 1);
            }
            else if (ilosc_gracz2 > ilosc_gracz1) {
                std::cout << "\nWygrywa komputer :(\n";
                z.wczytywanie_z_pliku(nick_1, 0);
            }
            else if (ilosc_gracz1 == ilosc_gracz2) {
                std::cout << "\nObie strony maja dokladnie tyle samo pionkow. \nNikt nie wygral, ale tez nikt nie przegral – remis!";
            }
        }
        std::cout << "\nKONIEC GRY!\n";
        // Wyświetlenie rankingu gracza
        z.ranking_tego_graczy(nick_1);
        // Wyświetlenie rankingu 5 najlepszych graczy
        z.najlepsi_graczy();

        delete gracz1;
        delete robot;
    }

    return 0;
}