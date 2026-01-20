#include "tablica.h"
#include "Kocka.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

Tablica::Tablica() {
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 12; r++) {
            stanje[s][r] = false;
            bodovi[s][r] = 0;
        }
    }
}
bool Tablica::upis(int stupac, int indeks, int vrijednost) {
    if (stupac < 0 || stupac >= 4 || indeks < 0 || indeks >= 12) {
        std::cout << "pogresan unos(krivi broj redaka i/ili stupaca)\n" << std::endl;
        return false;
    }

    if (stanje[stupac][indeks] == true) {
        std::cout << "polje vec popunjeno\n" << std::endl;
        return false;
    }
    bodovi[stupac][indeks] = vrijednost;
    stanje[stupac][indeks] = true;
    return true;
}
bool Tablica::popunjeno(int stupac, int red)const {
    if (stupac < 0 || stupac >= 4 || red < 0 || red >= 12) {
        std::cout << "krivi unos(nema tih stupaca/redova)\n" << std::endl;
        return false;
    }
    return stanje[stupac][red];
}
int Tablica::ukupniBodovi() const {
    int ukupno = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 12; r++) {
            if (stanje[s][r]) {
                ukupno += bodovi[s][r];
            }
        }
    }
    return ukupno;
}
bool Tablica::tablicaPopunjena() const {
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 12; r++) {
            if (!stanje[s][r]) {
                return false;
            }
        }
    }
    return true;
}

void Tablica::prikaz() const {
    std::string stupacNazivi[] = { "Gore", "Dole", "Gore-Dole", "     N" };
    std::string redNazivi[] = { "1", "2", "3", "4", "5", "6", "MAX", "MIN", "S", "F", "P", "Y" };

    std::cout << "            ";
    for (int s = 0; s < 4; s++) {
        std::cout << std::setw(12) << std::left << stupacNazivi[s];
    }
    std::cout << "\n";


    std::cout << "            ";
    for (int s = 0; s < 52; s++) {
        std::cout << '-';
    }
    std::cout << "\n";


    for (int r = 0; r < 12; r++) {

        std::cout << std::setw(12) << std::right << redNazivi[r] << "|";
        for (int s = 0; s < 4; s++) {
            if (stanje[s][r]) {

                std::cout << std::setw(12) << std::left << bodovi[s][r] << "|";
            }
            else {

                std::cout << std::setw(12) << std::left << "___" << "|";
            }
        }
        std::cout << "\n";
    }
}
