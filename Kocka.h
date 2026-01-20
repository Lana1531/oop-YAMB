#ifndef KOCKA_H
#define KOCKA_H
#include <vector>
#include <iostream>
class Kocka {
private:
	std::vector<int> kockice;
	std::vector<bool> zadrzane;
	int brojBacanja;
public:
	Kocka();
	void baci();
	void zakljucaj(int indeks);
	void reset();

	std::vector<int> getKockice()const;
	std::vector<bool> getZadrzane()const;
	int getBrojBacanja()const;

	int PonavljanjeBroj(int broj)const;
	void prikaz()const;
	bool MalaSkala() const;
	bool VelikaSkala() const;
	bool Full() const;
	bool Poker() const;
	bool Yamb() const;

	//Racunalo
	int najboljiBodovi()const;
	int najboljaKombinacija()const;
	std::vector<int> zadrzaneKockice()const;
};
#endif