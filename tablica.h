#ifndef TABLICA_H
#define TABLICA_H
#include <iostream>
class Kocka;
class Tablica {
private:
	int bodovi[4][12];
	bool stanje[4][12];
public:
	Tablica();
	bool upis(int stupac, int indeks, int vrijednost);
	bool popunjeno(int stupac, int red)const;
	void prikaz()const;

	int getBodovi(int stupac, int red)const {
		return bodovi[stupac][red];
	}
	bool getStanje(int stupac, int red)const {
		return stanje[stupac][red];
	}
	int ukupniBodovi() const;

	bool tablicaPopunjena()const;

};
#endif
