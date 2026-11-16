#include "Klocek.h"
#include <stdexcept>

Klocek::Klocek(int pozycjaX, int pozycjaY, int szerokoscKlocka, int wytrzymalosc, int punkty) : pozycjaX(pozycjaX), pozycjaY(pozycjaY), szerokoscKlocka(szerokoscKlocka), wytrzymalosc(wytrzymalosc), punkty(punkty) {
    if (szerokoscKlocka <= 0 || wytrzymalosc <= 0) {
        throw invalid_argument("Nieprawidlowe parametry klocka");
    }
}

Klocek::~Klocek() {
}

void Klocek::przyjmijUderzenie() {
    if (wytrzymalosc > 0) {
        wytrzymalosc--;
    }
}

bool Klocek::czyZniszczony() const {
    return wytrzymalosc <= 0;
}

int Klocek::getPozycjaX() const {
    return pozycjaX;
}

int Klocek::getPozycjaY() const {
    return pozycjaY;
}

int Klocek::getSzerokoscKlocka() const {
    return szerokoscKlocka;
}

int Klocek::getWytrzymalosc() const {
    return wytrzymalosc;
}

int Klocek::getPunkty() const {
    return punkty;
}

ostream& operator << (ostream& os, const Klocek& k) {
    os << "Klocek[x=" << k.pozycjaX << ", y=" << k.pozycjaY << ", hp=" << k.wytrzymalosc << "]";
    return os;
}