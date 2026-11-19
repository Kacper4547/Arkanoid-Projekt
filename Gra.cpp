#include "Gra.h"
#include "KlocekZwykly.h"
#include "KlocekUlepszony.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

Gra::Gra(int szerokoscPlanszy, int wysokoscPlanszy) : szerokoscPlanszy(szerokoscPlanszy), wysokoscPlanszy(wysokoscPlanszy), punkty(0), zycia(3), aktualnyPoziom(1), maksymalnyPoziom(3), zakonczona(false), wygrana(false), platforma(szerokoscPlanszy, wysokoscPlanszy, 11), kulka(szerokoscPlanszy, wysokoscPlanszy) {
    if (szerokoscPlanszy < 30 || wysokoscPlanszy < 15) {
        throw invalid_argument("Za male wymiary planszy gry");
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    wygenerujKlocki();
}

Gra::~Gra() {
    wyczyscKlocki();
}

void Gra::wyczyscKlocki() {
    for(size_t indeks = 0; indeks < klocki.size(); indeks++) {
        delete klocki[indeks];
    }

    klocki.clear();
}

void Gra::wygenerujKlocki() {
    wyczyscKlocki();
    int szerokoscKlocka = 5;
    int odstep = 1;
    int marginesBoczny = 4;
    int ostatniWiersz = 3 + aktualnyPoziom;
    int szansaNaUlepszony = 10 + (aktualnyPoziom * 25);

    for(int wiersz = 2; wiersz <= ostatniWiersz; wiersz++) {
        for(int kolumna = marginesBoczny; kolumna + szerokoscKlocka <= szerokoscPlanszy - marginesBoczny; kolumna += szerokoscKlocka + odstep) {
            int losowanie = rand() % 100;
            if (losowanie < szansaNaUlepszony) {
                klocki.push_back(new KlocekUlepszony(kolumna, wiersz, szerokoscKlocka));
            } else {
                klocki.push_back(new KlocekZwykly(kolumna, wiersz, szerokoscKlocka));
            }
        }
    }
}

void Gra::zresetujGre() {
    punkty = 0;
    zycia = 3;
    aktualnyPoziom = 1;
    zakonczona = false;
    wygrana = false;
    platforma.zresetujPozycje();
    kulka.zresetujPozycje();
    wygenerujKlocki();
}

void Gra::obsluzRuchPlatformy(int kierunek) {
    platforma.ruszaj(kierunek);
}

void Gra::sprawdzKolizjeZKlockami() {
    int kulkaX = kulka.getPozycjaX();
    int kulkaY = kulka.getPozycjaY();

    for(size_t indeks = 0; indeks < klocki.size(); indeks++) {
        if (klocki[indeks] -> czyZniszczony()) {
            continue;
        }

        int klocekX = klocki[indeks] -> getPozycjaX();
        int klocekY = klocki[indeks] -> getPozycjaY();
        int szerokoscKlocka = klocki[indeks] -> getSzerokoscKlocka();

        if (kulkaY == klocekY && kulkaX >= klocekX && kulkaX < klocekX + szerokoscKlocka) {
            klocki[indeks] -> przyjmijUderzenie();
            kulka.odbijY();

            if (klocki[indeks] -> czyZniszczony()) {
                punkty += klocki[indeks] -> getPunkty();
            }

            break;
        }
    }
}

void Gra::aktualizuj() {
    if (zakonczona) {
        return;
    }

    platforma.aktualizuj();
    kulka.aktualizuj(platforma);
    sprawdzKolizjeZKlockami();

    if (kulka.czyPrzegrana()) {
        zycia--;
        if (zycia <= 0) {
            zycia = 0;
            zakonczona = true;
            wygrana = false;
        } else {
            platforma.zresetujPozycje();
            kulka.zresetujPozycje();
        }
    }

    bool pozostalyAktywneKlocki = false;
    for(size_t indeks = 0; indeks < klocki.size(); indeks++) {
        if (!klocki[indeks] -> czyZniszczony()) {
            pozostalyAktywneKlocki = true;
            break;
        }
    }

    if (!pozostalyAktywneKlocki) {
        if (aktualnyPoziom < maksymalnyPoziom) {
            aktualnyPoziom++;
            platforma.zresetujPozycje();
            kulka.zresetujPozycje();
            wygenerujKlocki();
        } else {
            zakonczona = true;
            wygrana = true;
        }
    }
}

void Gra::rysujPlansze() const {
    vector<string> buforPlanszy(wysokoscPlanszy, string(szerokoscPlanszy, ' '));

    for(int pozycjaX = 0; pozycjaX < szerokoscPlanszy; pozycjaX++) {
        buforPlanszy[0][pozycjaX] = '#';
        buforPlanszy[wysokoscPlanszy - 1][pozycjaX] = '#';
    }

    for(int pozycjaY = 0; pozycjaY < wysokoscPlanszy; pozycjaY++) {
        buforPlanszy[pozycjaY][0] = '#';
        buforPlanszy[pozycjaY][szerokoscPlanszy - 1] = '#';
    }

    for(size_t indeks = 0; indeks < klocki.size(); indeks++) {
        if (!klocki[indeks] -> czyZniszczony()) {
            int klocekX = klocki[indeks] -> getPozycjaX();
            int klocekY = klocki[indeks] -> getPozycjaY();
            int szerokoscKlocka = klocki[indeks] -> getSzerokoscKlocka();
            char znakKlocka = klocki[indeks] -> getZnak();

            for (int przesuniecieX = 0; przesuniecieX < szerokoscKlocka; przesuniecieX++) {
                if (klocekX + przesuniecieX > 0 && klocekX + przesuniecieX < szerokoscPlanszy - 1) {
                    buforPlanszy[klocekY][klocekX + przesuniecieX] = znakKlocka;
                }
            }
        }
    }

    int platformaX = platforma.getPozycjaX();
    int platformaY = platforma.getPozycjaY();
    int szerokoscPlatformy = platforma.getSzerokoscPlatformy();
    for(int przesuniecieX = 0; przesuniecieX < szerokoscPlatformy; przesuniecieX++) {
        if (platformaX + przesuniecieX > 0 && platformaX + przesuniecieX < szerokoscPlanszy - 1) {
            buforPlanszy[platformaY][platformaX + przesuniecieX] = '=';
        }
    }

    int kulkaX = kulka.getPozycjaX();
    int kulkaY = kulka.getPozycjaY();
    if (kulkaX > 0 && kulkaX < szerokoscPlanszy - 1 && kulkaY > 0 && kulkaY < wysokoscPlanszy - 1) {
        buforPlanszy[kulkaY][kulkaX] = 'O';
    }

    cout << "Poziom: " << aktualnyPoziom << "/" << maksymalnyPoziom << "   Punkty: " << punkty << "   Zycia: " << zycia << "\n";
    for(int pozycjaY = 0; pozycjaY < wysokoscPlanszy; pozycjaY++) {
        cout << buforPlanszy[pozycjaY] << "\n";
    }
}

bool Gra::czyZakonczona() const {
    return zakonczona;
}

bool Gra::czyWygrana() const {
    return wygrana;
}

int Gra::getPunkty() const {
    return punkty;
}

int Gra::getZycia() const {
    return zycia;
}

int Gra::getAktualnyPoziom() const {
    return aktualnyPoziom;
}