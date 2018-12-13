#pragma once
#include"Rezervacija.h"

class Hotel {
	char* _naziv;  //Ponuda smještaja
	Smjestaj* _smjestaji;
	int _brojSmjestaja;  //Rezervacije hotela (protekle, aktivne i nadolazeće) 
	Rezervacija* _rezervacije;
	int _brojRezervacija;
	static int _stopaPDV;

public:
	Hotel();
	Hotel(const char*);
	Hotel(const Hotel&);
	Hotel(Hotel&&);
	~Hotel();

	Hotel& operator=(const Hotel&);
	Hotel& operator+=(const Smjestaj&);
	bool operator+=(const Rezervacija&);
	Smjestaj* operator[](int);
	Rezervacija* operator()(int);

	int trazenaRezervacija(Rezervacija&);
	int trazeniSmjestaj(Smjestaj);
	int zauzetSmjestaj(Smjestaj&);
	bool odobriSmjestaj(const Rezervacija&);
	Gost* getSveGoste(int&);

	char* getNaziv()const;
	int getBrojSmjestaja()const;
	int getBrojRezervacija()const;
	int getStopaPDV()const;

	void setNaziv(const char*);
	void PotvrdiRezervaciju(Rezervacija&);
	void CheckIn(Rezervacija&);
	void IspisiSlobodneSmjestaje(Datum, Datum);
	void CheckOut(Rezervacija&, bool);
	Smjestaj* GetNajTrazenijiSmjestaj(Datum, Datum);
	Gost* PronadjiVIPGosta();
	friend ostream& operator<<(ostream&, Hotel&);
	friend bool operator==(const Hotel&, const Hotel&);
};