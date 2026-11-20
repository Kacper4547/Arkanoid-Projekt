#include "Platforma.h"

Platforma::Platforma(): pozycjaX(25), pozycjaY(22), szerokoscPlatformy(11), bazowaSzerokosc(11), predkoscRuchu(3), kierunekRuchu(0), szerokoscPlanszy(60), wysokoscPlanszy(25) {
    zresetujPozycje();
}

Platforma::Platforma(int szerokoscPlanszy, int wysokoscPlanszy, int szerokoscPlatformy): pozycjaX(0), pozycjaY(0), szerokoscPlatformy(szerokoscPlatformy), bazowaSzerokosc(szerokoscPlatformy), predkoscRuchu(3), kierunekRuchu(0), szerokoscPlanszy(szerokoscPlanszy), wysokoscPlanszy(wysokoscPlanszy) {
    zresetujPozycje();
}

void Platforma::zresetujPozycje() {
    szerokoscPlatformy = bazowaSzerokosc;
    pozycjaX = (szerokoscPlanszy - szerokoscPlatformy) / 2;
    pozycjaY = wysokoscPlanszy - 2;
    kierunekRuchu = 0;
}

void Platforma::ruszaj(int kierunek) {
    pozycjaX += kierunek * predkoscRuchu;
    kierunekRuchu = kierunek;

    if (pozycjaX < 1) {
        pozycjaX = 1;
    }

    if (pozycjaX + szerokoscPlatformy >= szerokoscPlanszy - 1) {
        pozycjaX = szerokoscPlanszy - 1 - szerokoscPlatformy;
    }
}

void Platforma::aktualizuj() {
    kierunekRuchu = 0;
}

Platforma& Platforma::operator += (int zmianaSzerokosci) {
    int maksymalnaSzerokosc = 23;
    szerokoscPlatformy += zmianaSzerokosci;

    if (szerokoscPlatformy > maksymalnaSzerokosc) {
        szerokoscPlatformy = maksymalnaSzerokosc;
    }

    if (szerokoscPlatformy < 5) {
        szerokoscPlatformy = 5;
    }

    if (pozycjaX + szerokoscPlatformy >= szerokoscPlanszy - 1) {
        pozycjaX = szerokoscPlanszy - 1 - szerokoscPlatformy;
    }

    return *this;
}

int Platforma::getPozycjaX() const {
    return pozycjaX;
}

int Platforma::getPozycjaY() const {
    return pozycjaY;
}

int Platforma::getSzerokoscPlatformy() const {
    return szerokoscPlatformy;
}

int Platforma::getKierunekRuchu() const {
    return kierunekRuchu;
}

void Platforma::setPozycjaX(int nowaPozycjaX) {
    if (nowaPozycjaX >= 1 && nowaPozycjaX + szerokoscPlatformy < szerokoscPlanszy) {
        pozycjaX = nowaPozycjaX;
    }
}

ostream& operator << (ostream& os, const Platforma& p) {
    os << "Platforma[x=" << p.pozycjaX << ", y=" << p.pozycjaY << ", szer=" << p.szerokoscPlatformy << "]";
    return os;
}