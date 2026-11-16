#ifndef KLOCEK_H
#define KLOCEK_H

#include <iostream>

using namespace std;

class Klocek {
protected:
    int pozycjaX;
    int pozycjaY;
    int szerokoscKlocka;
    int wytrzymalosc;
    int punkty;

public:
    Klocek(int pozycjaX, int pozycjaY, int szerokoscKlocka, int wytrzymalosc, int punkty);
    virtual ~Klocek();

    virtual void przyjmijUderzenie();
    virtual char getZnak() const = 0;

    bool czyZniszczony() const;
    int getPozycjaX() const;
    int getPozycjaY() const;
    int getSzerokoscKlocka() const;
    int getWytrzymalosc() const;
    int getPunkty() const;

    friend ostream& operator << (ostream& os, const Klocek& k);
};

#endif