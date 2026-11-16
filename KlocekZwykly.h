#ifndef KLOCEKZWYKLY_H
#define KLOCEKZWYKLY_H

#include "Klocek.h"

class KlocekZwykly : public Klocek {
public:
    KlocekZwykly(int pozycjaX, int pozycjaY, int szerokoscKlocka = 5);
    char getZnak() const override;
};

#endif