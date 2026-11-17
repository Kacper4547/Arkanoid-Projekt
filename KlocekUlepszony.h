#ifndef KLOCEKULEPSZONY_H
#define KLOCEKULEPSZONY_H

#include "Klocek.h"

class KlocekUlepszony : public Klocek {
public:
    KlocekUlepszony(int pozycjaX, int pozycjaY, int szerokoscKlocka = 5);
    void przyjmijUderzenie() override;
    char getZnak() const override;
};

#endif