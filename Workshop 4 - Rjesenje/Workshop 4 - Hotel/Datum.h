#pragma once
#include<iostream>
using namespace std;

class Datum {
	int _dan;
	int _mjesec;
	int _godina;

public:
	Datum();
	Datum(int, int, int);
	
	Datum& operator=(const Datum&);
	bool izmedju(Datum, Datum);
	int suma();
	int getGodinu()const;
	friend ostream& operator<<(ostream&,Datum&);
	friend bool operator==(const Datum&, const Datum&);
};