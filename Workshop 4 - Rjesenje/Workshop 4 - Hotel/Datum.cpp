#include"pch.h"


Datum::Datum() { _dan = _mjesec = _godina = 0; }

Datum::Datum(int d, int m, int g) : _dan(d), _mjesec(m), _godina(g) {}

Datum& Datum::operator=(const Datum& date) {
	if (&date == this)
		return *this;
	_dan = date._dan;
	_mjesec = date._mjesec;
	_godina = date._godina;
	return *this;
}
bool Datum::izmedju(Datum d1, Datum d2) {
	return (this->suma() <= d2.suma() && this->suma() >= d1.suma());
}
int Datum::suma() { return _dan + (_mjesec * 31) + (_godina * 365); }
int Datum::getGodinu()const { return _godina; }
ostream& operator<<(ostream& COUT,Datum& date) {
	cout << date._dan << "/" << date._mjesec << "/" << date._godina << endl;
	return COUT;
}

bool operator==(const Datum& d1, const Datum& d2) {
	return d1._dan == d2._dan && d1._mjesec == d2._mjesec && d1._godina == d2._godina;
}

	

