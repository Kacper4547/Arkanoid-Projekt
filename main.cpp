#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdexcept>
#include "Gra.h"

using namespace std;

// 1. Kompilacja gry w konsoli:
// g++ main.cpp Gra.cpp Platforma.cpp Kulka.cpp Klocek.cpp KlocekZwykly.cpp KlocekUlepszony.cpp -o arkanoid.exe
// 2. Uruchomienie gry w konsoli:
// arkanoid.exe
// 3. Sterowanie:
// A / D lub strzalki lewo / prawo, R - restart, Q / ESC - wyjscie

void ustawKursor(int pozycjaX, int pozycjaY) {
    COORD wspolrzedne;
    wspolrzedne.X = static_cast<SHORT>(pozycjaX);
    wspolrzedne.Y = static_cast<SHORT>(pozycjaY);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), wspolrzedne);
}

void ukryjKursor() {
    HANDLE uchwytKonsoli = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO informacjeKursora;
    GetConsoleCursorInfo(uchwytKonsoli, &informacjeKursora);
    informacjeKursora.bVisible = FALSE;
    SetConsoleCursorInfo(uchwytKonsoli, &informacjeKursora);
}

int main() {
    try {
        ukryjKursor();
        system("cls");

        Gra gra(60, 25);
        bool dziala = true;

        while (dziala) {
            if (_kbhit()) {
                int klawisz = _getch();

                if (klawisz == 0 || klawisz == 224) {
                    int kodStrzalki = _getch();
                    if (kodStrzalki == 75) {
                        gra.obsluzRuchPlatformy(-1);
                    } else if (kodStrzalki == 77) {
                        gra.obsluzRuchPlatformy(1);
                    }
                } else {
                    if (klawisz == 'a' || klawisz == 'A') {
                        gra.obsluzRuchPlatformy(-1);
                    } else if (klawisz == 'd' || klawisz == 'D') {
                        gra.obsluzRuchPlatformy(1);
                    } else if (klawisz == 'r' || klawisz == 'R') {
                        if (gra.czyZakonczona()) {
                            system("cls");
                            gra.zresetujGre();
                        }
                    } else if (klawisz == 'q' || klawisz == 'Q' || klawisz == 27) {
                        dziala = false;
                    }
                }
            }

            gra.aktualizuj();
            ustawKursor(0, 0);
            gra.rysujPlansze();
            cout << "Sterowanie: A/D lub strzalki - ruch | Q/ESC - wyjscie          \n";

            if (gra.czyZakonczona()) {
                if (gra.czyWygrana()) {
                    cout << "GRATULACJE! Ukonczyles wszystkie poziomy! Wynik: " << gra.getPunkty() << "   \n";
                } else {
                    cout << "KONIEC GRY! Straciles wszystkie zycia. Wynik: " << gra.getPunkty() << "   \n";
                }
                cout << "Podsumowanie: " << gra << "\n";
                cout << "Nacisnij R, aby zagrac ponownie, lub Q, aby wyjsc.          \n";
            }

            Sleep(55);
        }
    } catch (const exception& wyjatek) {
        cerr << "Blad krytyczny aplikacji: " << wyjatek.what() << "\n";
        return 1;
    }

    return 0;
}