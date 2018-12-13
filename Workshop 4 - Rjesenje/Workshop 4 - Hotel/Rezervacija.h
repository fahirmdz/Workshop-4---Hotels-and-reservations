#pragma once
#include"Datum.h"
#include"Smjestaj.h"
#include"Gost.h"
#include"Usluga.h"

enum StatusRezervacije { Aktivna, Potvrdjena, BoravakUToku, Otkazana };

class Rezervacija {
	Datum _pocetakBoravka;
	Datum _krajBoravka;
	Gost* _gost; //Gost koji je rezervisao smještaj 
	Smjestaj _smjestaj;
	int _brojOsoba; //Ukupan broj osoba koji boravi u smjestaju 
	Usluga* _usluge; //Dodatne usluge koje je gost koristio tokom boravka 
	int _brojUsluga;
	double _ukupanIznos;
	StatusRezervacije _status;

public:
	Rezervacija();
	Rezervacija(Datum, Datum,Gost&, Smjestaj&, int);
	Rezervacija(const Rezervacija&);
	Rezervacija(Rezervacija&&);
	~Rezervacija();

	Rezervacija& operator=(const Rezervacija&);
	Rezervacija& operator+=(const Usluga&);
	Usluga* operator[](int);

	Datum getDatumPocetka()const;
	Datum getDatumKraja()const;
	Gost* getGost()const;
	Smjestaj getSmjestaj()const;
	int getBrojOsoba()const;
	int getBrojUsluga()const;
	double getIznos()const;
	char* getStatusChar()const;
	StatusRezervacije getStatus()const;

	void setStatus(StatusRezervacije);

	friend ostream& operator<<(ostream&, Rezervacija&);
	friend bool operator==(const Rezervacija&, const Rezervacija&);
};