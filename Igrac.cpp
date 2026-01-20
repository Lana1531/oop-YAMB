#include "Igrac.h"
#include <iostream>

Igrac::Igrac(std::string ime, bool racunalo)
	:ime(ime), racunalo(racunalo) {}

std::string Igrac::getIme()const {
	return ime;
}
Tablica& Igrac::getTablica() {
	return tablica;
}
void Igrac::tablicaIgraca()const {
	std::cout << "\nime: " << ime << "\n";
	tablica.prikaz();
}


bool Igrac::mozeUpisati(int stupac, int red)const {
	if (stupac < 0 || stupac >3 || red < 0 || red >11) {
		return false;
	}
	if (tablica.getStanje(stupac, red)) {
		return false;
	}
	if (stupac == 0) {
		for (int i = 0; i < red; i++) {
			if (!tablica.getStanje(stupac, i)) {
				return false;
			}
		}
	}
	else if (stupac == 1) {
		for (int i = red + 1; i < 12; i++) {
			if (!tablica.getStanje(stupac, i)) {
				return false;
			}
		}
	}
	return true;
}