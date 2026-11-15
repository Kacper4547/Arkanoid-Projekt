#ifndef PLATFORMA_H
#define PLATFORMA_H

#include <iostream>

using namespace std;

class Platforma {
private:
    int pozycjaX;
    int pozycjaY;
    int szerokoscPlatformy;
    int predkoscRuchu;
    int kierunekRuchu;
    int szerokoscPlanszy;
    int wysokoscPlanszy;

public:
    Platforma();
    Platforma(int szerokoscPlanszy, int wysokoscPlanszy, int szerokoscPlatformy = 11);

    void zresetujPozycje();
    void ruszaj(int kierunek);
    void aktualizuj();

    int getPozycjaX() const;
    int getPozycjaY() const;
    int getSzerokoscPlatformy() const;
    int getKierunekRuchu() const;

    void setPozycjaX(int nowaPozycjaX);

    friend ostream& operator << (ostream& os, const Platforma& p);
};

#endif