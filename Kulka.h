#ifndef KULKA_H
#define KULKA_H

#include <iostream>
#include "Platforma.h"

using namespace std;

class Kulka {
private:
    double pozycjaX;
    double pozycjaY;
    double predkoscX;
    double predkoscY;
    int szerokoscPlanszy;
    int wysokoscPlanszy;
    bool przegrana;

public:
    Kulka();
    Kulka(int szerokoscPlanszy, int wysokoscPlanszy);

    void zresetujPozycje();
    void aktualizuj(const Platforma& platforma);
    void odbijX();
    void odbijY();

    int getPozycjaX() const;
    int getPozycjaY() const;
    double getDokladnaPozycjaX() const;
    double getDokladnaPozycjaY() const;
    double getPredkoscX() const;
    double getPredkoscY() const;
    bool czyPrzegrana() const;

    void setPozycja(double nowaPozycjaX, double nowaPozycjaY);
    void setPredkosc(double nowaPredkoscX, double nowaPredkoscY);

    bool operator == (const Kulka& inna) const;
    friend ostream& operator << (ostream& os, const Kulka& k);
};

#endif