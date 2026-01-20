#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "Tablica.h"
#include "Kocka.h"
#include "Igrac.h"
using namespace std;

vector<int> zadrziKockice(const Kocka& kocka) {
    vector<int> odabrane;
    string unos;
    getline(cin, unos);
    for (char c : unos) {
        if (c >= '0' && c <= '4') {
            odabrane.push_back(c - '0');
        }
    }
    return odabrane;
}

void prikaziKombinacije(const Kocka& kocka) {
    cout << "\nMala skala(1-5): " << (kocka.MalaSkala() ? "DA" : "NE") << endl;
    cout << "Velika Skala(2-6): " << (kocka.VelikaSkala() ? "DA" : "NE") << endl;
    cout << "Full(2+3): " << (kocka.Full() ? "DA" : "NE") << endl;
    cout << "Poker(4): " << (kocka.Poker() ? "DA" : "NE") << endl;
    cout << "Yamb(5): " << (kocka.Yamb() ? "DA" : "NE") << endl;

    for (int broj = 1; broj <= 6; broj++) {
        int brojac = kocka.PonavljanjeBroj(broj);
        cout << "\nBroj " << broj << ": " << (brojac * broj) << " boda";
    }

    vector<int> k = kocka.getKockice();
    int zbroj = 0;
    for (int kockica : k) {
        zbroj += kockica;
    }
    cout << "\nZbroj: " << zbroj << " (MAX >25, MIN <15)\n";
}

int izracunajBodove(const Kocka& kocka, int indeks) {
    int bodovi = 0;
    vector<int> k = kocka.getKockice();

    if (indeks >= 0 && indeks <= 5) {
        int broj = indeks + 1;
        int brojac = kocka.PonavljanjeBroj(broj);
        bodovi = brojac * broj;
    }
    else if (indeks == 6) {
        for (int kockica : k) bodovi += kockica;
        if (bodovi <= 25) bodovi = 0;
    }
    else if (indeks == 7) {
        for (int kockica : k) bodovi += kockica;
        if (bodovi >= 15) bodovi = 0;
    }
    else if (indeks == 8) {
        if (kocka.MalaSkala()) bodovi = 35;
        else if (kocka.VelikaSkala()) bodovi = 45;
    }
    else if (indeks == 9) {
        if (kocka.Full()) {
            for (int kockica : k) bodovi += kockica;
            bodovi += 30;
        }
    }
    else if (indeks == 10) {
        if (kocka.Poker()) {
            for (int kockica : k) bodovi += kockica;
            bodovi += 40;
        }
    }
    else if (indeks == 11) {
        if (kocka.Yamb()) bodovi = 50;
    }

    return bodovi;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "           YAMB       \n\n";

    int brojIgraca;
    cout << "Broj igraca (1 ili 2): ";
    cin >> brojIgraca;
    cin.ignore(1000, '\n');

    Igrac igrac1, igrac2;

    if (brojIgraca == 1) {
        string ime;
        cout << "Ime igraca: ";
        getline(cin, ime);

        igrac1 = Igrac(ime, false);
        igrac2 = Igrac("Racunalo", true);
    }
    else {
        string ime1, ime2;
        cout << "Ime prvog igraca: ";
        getline(cin, ime1);
        cout << "Ime drugog igraca: ";
        getline(cin, ime2);

        igrac1 = Igrac(ime1, false);
        igrac2 = Igrac(ime2, false);
    }

    Kocka kocka;
    bool igraTraje = true;
    Igrac* trenutniIgrac = &igrac1;

    while (igraTraje) {
        cout << "\n      " << trenutniIgrac->getIme() << "\n";
        bool narav = false;
        int naravRed = -1;

        if (!trenutniIgrac->jeRacunalo()) {
            int odgovor;
            cout << "Igrati N(1/0): ";
            cin >> odgovor;
            cin.ignore(1000, '\n');

            if (odgovor == 1) {
                narav = true;

                string redUnos;
                cout << "red: ";
                cin >> redUnos;
                cin.ignore(1000, '\n');

                if (redUnos == "1") naravRed = 0;
                else if (redUnos == "2") naravRed = 1;
                else if (redUnos == "3") naravRed = 2;
                else if (redUnos == "4") naravRed = 3;
                else if (redUnos == "5") naravRed = 4;
                else if (redUnos == "6") naravRed = 5;
                else if (redUnos == "max") naravRed = 6;
                else if (redUnos == "min") naravRed = 7;
                else if (redUnos == "s") naravRed = 8;
                else if (redUnos == "f") naravRed = 9;
                else if (redUnos == "p") naravRed = 10;
                else if (redUnos == "y") naravRed = 11;
                else {
                    cout << "Krivi unos\n";
                    narav = false;
                }
            }
        }

        kocka.reset();
        bool potezZavrsen = false;

        if (trenutniIgrac->jeRacunalo()) {
            for (int bacanje = 0; bacanje < 3; bacanje++) {
                kocka.baci();
                kocka.prikaz();
                cout << "        (" << kocka.getBrojBacanja() << "/3)" << "\n";

                if (bacanje < 2) {
                    auto zadrzi = kocka.zadrzaneKockice();
                    for (int i : zadrzi) {
                        kocka.zakljucaj(i);
                    }
                }
            }
            potezZavrsen = true;
        }
        else {
            while (!potezZavrsen && kocka.getBrojBacanja() < 3) {
                kocka.baci();
                kocka.prikaz();
                cout << "        (" << kocka.getBrojBacanja() << "/3)" << "\n";

                if (kocka.getBrojBacanja() < 3) {
                    cout << "1. Zakljucaj kockice\n";
                    cout << "2. Baci ponovno\n";
                    cout << "3. Upisi\n";
                    cout << "Odabir: ";

                    int izbor;
                    cin >> izbor;
                    cin.ignore(1000, '\n');

                    if (izbor == 1) {
                        vector<int> zadrzi = zadrziKockice(kocka);
                        for (int i : zadrzi) {
                            kocka.zakljucaj(i);
                        }
                    }
                    else if (izbor == 2) {
                        continue;
                    }
                    else if (izbor == 3) {
                        potezZavrsen = true;
                    }
                    else {
                        cout << "Neispravan odabir\n";
                    }
                }
                else {
                    potezZavrsen = true;
                }
            }
        }

        if (!trenutniIgrac->jeRacunalo() && !narav) {
            prikaziKombinacije(kocka);
        }
        int stupac, indeks, bodovi = 0;
        if (trenutniIgrac->jeRacunalo()) {
            indeks = kocka.najboljaKombinacija();

            stupac = 2;
            if (trenutniIgrac->mozeUpisati(2, indeks)) {
                stupac = 2;
            }
            else if (trenutniIgrac->mozeUpisati(0, indeks)) {
                stupac = 0;
            }
            else if (trenutniIgrac->mozeUpisati(1, indeks)) {
                stupac = 1;
            }
            else if (trenutniIgrac->mozeUpisati(3, indeks)) {
                stupac = 3;
            }

            bodovi = izracunajBodove(kocka, indeks);
            cout << "\nRacunalo: stupac " << stupac << ", bodovi: " << bodovi << endl;

            if (!trenutniIgrac->getTablica().upis(stupac, indeks, bodovi)) {
                cout << "ne moze upisati na odabrano mjesto\n";
            }
            else {
                trenutniIgrac->tablicaIgraca();
            }
        }
        else {
            if (narav) {
                stupac = 3;
                indeks = naravRed;
                bodovi = izracunajBodove(kocka, indeks);
            }
            else {
                trenutniIgrac->tablicaIgraca();

                bool validan = false;
                while (!validan) {
                    cout << "Stupac(0-3): ";
                    cin >> stupac;
                    cin.ignore(1000, '\n');

                    string red;
                    cout << "Red: ";
                    cin >> red;
                    cin.ignore(1000, '\n');

                    indeks = -1;
                    if (red == "1") indeks = 0;
                    else if (red == "2") indeks = 1;
                    else if (red == "3") indeks = 2;
                    else if (red == "4") indeks = 3;
                    else if (red == "5") indeks = 4;
                    else if (red == "6") indeks = 5;
                    else if (red == "max") indeks = 6;
                    else if (red == "min") indeks = 7;
                    else if (red == "s") indeks = 8;
                    else if (red == "f") indeks = 9;
                    else if (red == "p") indeks = 10;
                    else if (red == "y") indeks = 11;
                    else {
                        cout << "Neispravan unos reda\n";
                        continue;
                    }
                    if (!trenutniIgrac->mozeUpisati(stupac, indeks)) {
                        cout << "Ne mozete upisati na to mjesto\n";

                        if (stupac == 0) {
                            cout << "GORE: Morate prvo popuniti iznad\n";
                        }
                        else if (stupac == 1) {
                            cout << "DOLE: Morate prvo popuniti ispod\n";
                        }
                        else if (stupac == 3) {
                            cout << "NARAV: Niste najavili prije bacanja\n";
                        }
                        continue;
                    }

                    validan = true;
                }

                bodovi = izracunajBodove(kocka, indeks);
            }
            if (!trenutniIgrac->getTablica().upis(stupac, indeks, bodovi)) {
                cout << "Polje vec popunjeno ili krivi unos\n";
            }
            else {
                trenutniIgrac->tablicaIgraca();
            }
            if (igrac1.getTablica().tablicaPopunjena() && igrac2.getTablica().tablicaPopunjena()) {
                igraTraje = false;
                cout << " Oba igraca su popunila tablice!\n";
            }
        }
        if (trenutniIgrac == &igrac1) {
            trenutniIgrac = &igrac2;
        }
        else {
            trenutniIgrac = &igrac1;
        }
        if (igraTraje) {
            cin.get();
        }
    }

    cout << "\nREZULTATI:\n";
    cout << igrac1.getIme() << ": " << igrac1.getTablica().ukupniBodovi() << " bodova\n";
    cout << igrac2.getIme() << ": " << igrac2.getTablica().ukupniBodovi() << " bodova\n";

    if (igrac1.getTablica().ukupniBodovi() > igrac2.getTablica().ukupniBodovi()) {
        cout << "\nPOBJEDNIK JE: " << igrac1.getIme() << "!\n";
    }
    else if (igrac1.getTablica().ukupniBodovi() < igrac2.getTablica().ukupniBodovi()) {
        cout << "\nPOBJEDNIK JE: " << igrac2.getIme() << "!\n";
    }
    else {
        cout << "\nNERIJESENO\n";
    }

    return 0;
}