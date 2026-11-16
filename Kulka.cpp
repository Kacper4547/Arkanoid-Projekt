#include "Kulka.h"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

Kulka::Kulka() : pozycjaX(30.0), pozycjaY(21.0), predkoscX(0.5), predkoscY(-1.0), szerokoscPlanszy(60), wysokoscPlanszy(25), przegrana(false) {
    zresetujPozycje();
}

Kulka::Kulka(int szerokoscPlanszy, int wysokoscPlanszy) : pozycjaX(0.0), pozycjaY(0.0), predkoscX(0.0), predkoscY(0.0), szerokoscPlanszy(szerokoscPlanszy), wysokoscPlanszy(wysokoscPlanszy), przegrana(false) {
    if (szerokoscPlanszy < 10 || wysokoscPlanszy < 10) {
        throw invalid_argument("Za male wymiary planszy");
    }

    zresetujPozycje();
}

void Kulka::zresetujPozycje() {
    pozycjaX = szerokoscPlanszy / 2.0;
    pozycjaY = wysokoscPlanszy - 3.0;
    int losowyKierunek = (rand() % 3) - 1;
    predkoscX = losowyKierunek * 0.5;

    if (predkoscX == 0.0) {
        predkoscX = 0.5;
    }

    predkoscY = -1.0;
    przegrana = false;
}

void Kulka::aktualizuj(const Platforma& platforma) {
    pozycjaX += predkoscX;
    pozycjaY += predkoscY;

    if (pozycjaX <= 1.0) {
        pozycjaX = 1.0;
        odbijX();
    }

    if (pozycjaX >= szerokoscPlanszy - 2.0) {
        pozycjaX = szerokoscPlanszy - 2.0;
        odbijX();
    }

    if (pozycjaY <= 1.0) {
        pozycjaY = 1.0;
        odbijY();
    }

    int zaokragloneX = static_cast<int>(round(pozycjaX));
    int zaokragloneY = static_cast<int>(round(pozycjaY));

    if (predkoscY > 0 && zaokragloneY == platforma.getPozycjaY() - 1) {
        if (zaokragloneX >= platforma.getPozycjaX() && zaokragloneX < platforma.getPozycjaX() + platforma.getSzerokoscPlatformy()) {
            odbijY();
            predkoscX += platforma.getKierunekRuchu() * 0.4;

            if (predkoscX < -1.5) {
                predkoscX = -1.5;
            }

            if (predkoscX > 1.5) {
                predkoscX = 1.5;
            }
        }
    }

    if (pozycjaY >= wysokoscPlanszy - 1.0) {
        przegrana = true;
    }
}

void Kulka::odbijX() {
    predkoscX = -predkoscX;
}

void Kulka::odbijY() {
    predkoscY = -predkoscY;
}

int Kulka::getPozycjaX() const {
    return static_cast<int>(round(pozycjaX));
}

int Kulka::getPozycjaY() const {
    return static_cast<int>(round(pozycjaY));
}

double Kulka::getDokladnaPozycjaX() const {
    return pozycjaX;
}

double Kulka::getDokladnaPozycjaY() const {
    return pozycjaY;
}

double Kulka::getPredkoscX() const {
    return predkoscX;
}

double Kulka::getPredkoscY() const {
    return predkoscY;
}

bool Kulka::czyPrzegrana() const {
    return przegrana;
}

void Kulka::setPozycja(double nowaPozycjaX, double nowaPozycjaY) {
    if (nowaPozycjaX < 1.0 || nowaPozycjaX >= szerokoscPlanszy - 1.0 || nowaPozycjaY < 1.0 || nowaPozycjaY >= wysokoscPlanszy - 1.0) {
        throw out_of_range("Pozycja kulki poza plansza");
    }
    pozycjaX = nowaPozycjaX;
    pozycjaY = nowaPozycjaY;
}

void Kulka::setPredkosc(double nowaPredkoscX, double nowaPredkoscY) {
    predkoscX = nowaPredkoscX;
    predkoscY = nowaPredkoscY;
}

bool Kulka::operator == (const Kulka& inna) const {
    return getPozycjaX() == inna.getPozycjaX() && getPozycjaY() == inna.getPozycjaY();
}

ostream& operator << (ostream& os, const Kulka& k) {
    os << "Kulka[x=" << k.getPozycjaX() << ", y=" << k.getPozycjaY() << ", vx=" << k.predkoscX << ", vy=" << k.predkoscY << "]";
    return os;
}