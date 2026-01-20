#include "Kocka.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>  

Kocka::Kocka(){}

void Kocka::reset() {
    kockice = std::vector<int>(5, 1);
    zadrzane = std::vector<bool>(5, false);
    brojBacanja = 0;
}
void Kocka::baci() {
    if (brojBacanja >= 3) {
        std::cout << "ne mozete vise bacati\n" << std::endl;
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (!zadrzane[i]) {
            kockice[i] = rand() % 6 + 1;
        }
    }
    brojBacanja++;
}
void Kocka::zakljucaj(int indeks) {
    if (indeks >= 0 && indeks < 5) {
        zadrzane[indeks] = !zadrzane[indeks];
    }
}
std::vector<int> Kocka::getKockice()const {
    return kockice;
}
std::vector<bool> Kocka::getZadrzane()const {
    return zadrzane;
}
int Kocka::getBrojBacanja()const {
    return brojBacanja;
}

void Kocka::prikaz()const {
    std::cout << "\nkockice: ";
    for (int i = 0; i < 5; i++) {
        if (zadrzane[i]) {
            std::cout << " [" << kockice[i] << "] ";
        }
        else {
            std::cout << kockice[i] << " ";
        }
    }
}
int Kocka::PonavljanjeBroj(int broj)const {
    int brojac = 0;
    for (int k : kockice) {
        if (k == broj) {
            brojac++;
        }
    }
    return brojac;
}
bool Kocka::MalaSkala()const {
    std::vector<int> kopija = kockice;
    std::sort(kopija.begin(), kopija.end());
    kopija.erase(std::unique(kopija.begin(), kopija.end()), kopija.end());
    if (kopija.size() == 5 && kopija[0] == 1 && kopija[4] == 5) {
        return true;
    }
    return false;
}
bool Kocka::VelikaSkala()const {
    std::vector<int>kopija = kockice;
    std::sort(kopija.begin(), kopija.end());
    kopija.erase(std::unique(kopija.begin(), kopija.end()), kopija.end());
    if (kopija.size() == 5 && kopija[0] == 2 && kopija[4] == 6) {
        return true;
    }
    return false;
}

bool Kocka::Full()const {
    int brojac[7] = { 0 };
    for (int k : kockice) {
        brojac[k]++;
    }
    for (int i = 1; i <= 6; i++) {
        if (brojac[i] >= 3) {
            for (int j = 1; j <= 6; j++) {
                if (j != i && brojac[j] == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Kocka::Poker()const {
    int brojac[7] = { 0 };
    for (int k : kockice) {
        brojac[k]++;
    }
    for (int i = 1; i <= 6; i++) {
        if (brojac[i] >= 4) {
            return true;
        }
    }
    return false;
}
bool Kocka::Yamb()const {
    int prvi = kockice[0];
    for (int i = 1; i < 5; i++) {
        if (kockice[i] != prvi) {
            return false;
        }
    }
    return true;
}
//racunalo
int Kocka::najboljiBodovi()const {
    int najboljiBroj = 1;
    int najboljiBodovi = 0;
    for (int broj = 1; broj <= 6; broj++) {
        int brojac = PonavljanjeBroj(broj);
        int bodovi = brojac * broj;
        if (bodovi > najboljiBodovi) {
            najboljiBodovi = bodovi;
            najboljiBroj = broj;
        }
    }
    return najboljiBroj;
}
int Kocka::najboljaKombinacija()const {
    if (Yamb()) {
        return 11;
    }
    if (Poker()) {
        return 10;
    }
    if (Full()) {
        return 9;
    }
    if (VelikaSkala()) {
        return 8;
    }
    if (MalaSkala()) {
        return 8;
    }

    int zbroj = 0;
    for (int k : kockice) {
        zbroj += k;
    }
    if (zbroj > 25) {
        return 6;//max
    }
    else if (zbroj < 15) {
        return 7;//min
    }
    return najboljiBodovi() - 1;
}
std::vector<int> Kocka::zadrzaneKockice()const {
    std::vector < int > zadrzi;
    int broj = najboljiBodovi();
    for (int i = 0; i < 5; i++) {
        if (kockice[i] == broj) {
            zadrzi.push_back(i);
        }
    }
    return zadrzi;
}
