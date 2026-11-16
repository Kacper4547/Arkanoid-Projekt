#include "KlocekZwykly.h"

KlocekZwykly::KlocekZwykly(int pozycjaX, int pozycjaY, int szerokoscKlocka) : Klocek(pozycjaX, pozycjaY, szerokoscKlocka, 1, 10) {
}

char KlocekZwykly::getZnak() const {
    return '=';
}