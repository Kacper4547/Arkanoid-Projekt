#ifndef GRA_H
#define GRA_H

#include <vector>
#include <iostream>
#include "Platforma.h"
#include "Kulka.h"
#include "Klocek.h"

using namespace std;

class Gra {
private:
    int szerokoscPlanszy;
    int wysokoscPlanszy;
    int punkty;
    int zycia;
    int aktualnyPoziom;
    int maksymalnyPoziom;
    bool zakonczona;
    bool wygrana;

    Platforma platforma;
    Kulka kulka;
    vector<Klocek*> klocki;

    void wygenerujKlocki();
    void wyczyscKlocki();
    void sprawdzKolizjeZKlockami();

public:
    Gra(int szerokoscPlanszy = 60, int wysokoscPlanszy = 25);
    ~Gra();

    void zresetujGre();
    void obsluzRuchPlatformy(int kierunek);
    void aktualizuj();
    void rysujPlansze() const;

    bool czyZakonczona() const;
    bool czyWygrana() const;
    int getPunkty() const;
    int getZycia() const;
    int getAktualnyPoziom() const;

    friend ostream& operator << (ostream& os, const Gra& gra);
};

#endif