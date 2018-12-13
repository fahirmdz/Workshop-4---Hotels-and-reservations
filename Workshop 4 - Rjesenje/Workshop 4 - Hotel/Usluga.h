#pragma once
#include<iostream>
using namespace std;

enum TipNaplate { PoOsobi, Jednokratno, PoNocenju };
class Usluga {
	char* _naziv;
	double _cijena;
	TipNaplate _tipNaplate;

public:
	Usluga();
	Usluga(const char*, int, TipNaplate);
	Usluga(const Usluga&);
	Usluga(Usluga&&);
	~Usluga();

	Usluga& operator=(const Usluga&);

	char* getNaziv()const;
	double getCijena()const;
	char* getTipNaplate()const;

	void setNaziv(const char*);
	void setCijenu(double);
	void obracunajPDV(double);
	friend ostream& operator<<(ostream&, Usluga&);
	friend bool operator==(const Usluga&, const Usluga&);
};