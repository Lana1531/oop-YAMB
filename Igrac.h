#ifndef IGRAC_H
#define IGRAC_H
#include <string>
#include "Tablica.h"
#include "Kocka.h"

class Igrac {
private:
	std::string ime;
	Tablica tablica;
	bool racunalo;
public:
	Igrac(std::string ime = "igrac", bool racunalo = false);

	std::string getIme()const;
	Tablica& getTablica();
	void tablicaIgraca()const;

	bool jeRacunalo()const {
		return racunalo;
	}
	bool mozeUpisati(int stupac, int red)const;
};
#endif

