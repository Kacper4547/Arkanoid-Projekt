#include "KlocekUlepszony.h"

KlocekUlepszony::KlocekUlepszony(int pozycjaX, int pozycjaY, int szerokoscKlocka) : Klocek(pozycjaX, pozycjaY, szerokoscKlocka, 2, 25) {
}

void KlocekUlepszony::przyjmijUderzenie() {
    Klocek::przyjmijUderzenie();
}

char KlocekUlepszony::getZnak() const {
    if (wytrzymalosc > 1) {
        return '#';
    }
    return '=';
}