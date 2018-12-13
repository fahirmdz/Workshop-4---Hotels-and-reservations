#pragma once
#include<iostream>
using namespace std;

enum TipSmjestaja { StudioApartman, SingleRoom, DoubleRoom, SuperiorApartman };

class Smjestaj {
	int _broj; //Broj sobe, apartmana
	TipSmjestaja* _tipSmjestaja;
	int _maxBrojOsoba;
	double _cijenaPoOsobi;

public:
	Smjestaj();
	Smjestaj(int, TipSmjestaja, int, double);
	Smjestaj(const Smjestaj&);
	Smjestaj(Smjestaj&&);
	~Smjestaj();

	Smjestaj& operator=(const Smjestaj&);
	
	int getBrojSmjestaja()const;
	int getMaxOsoba()const;
	double getCijena()const;
	char* getTipSmjestaja()const;

	void setMaxOsoba(int);
	void setCijenaPoOsobi(double);

	friend ostream& operator<<(ostream&, Smjestaj&);
	friend bool operator==(const Smjestaj&, const Smjestaj&);

};