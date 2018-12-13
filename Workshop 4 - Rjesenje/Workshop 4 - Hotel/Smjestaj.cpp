#include "pch.h"

const char* TipSmjestajaString[] = { "StudioApartman", "SingleRoom", "DoubleRoom", "SuperiorApartman" };

Smjestaj::Smjestaj():_broj(0),_maxBrojOsoba(0),_cijenaPoOsobi(0),_tipSmjestaja(new TipSmjestaja(StudioApartman)) {}
     
Smjestaj::Smjestaj(int broj, TipSmjestaja tip, int maxBrojOsoba, double cijenaPoOsobi) : _broj(broj),
_tipSmjestaja(new TipSmjestaja(tip)), _maxBrojOsoba(maxBrojOsoba), _cijenaPoOsobi(cijenaPoOsobi) {  }

Smjestaj::Smjestaj(const Smjestaj& sm):_broj(sm._broj),_maxBrojOsoba(sm._maxBrojOsoba),_cijenaPoOsobi(sm._cijenaPoOsobi),
_tipSmjestaja(new TipSmjestaja(*sm._tipSmjestaja)){}

Smjestaj::Smjestaj(Smjestaj&& sm) {
	_tipSmjestaja = sm._tipSmjestaja;
	sm._tipSmjestaja = nullptr;
	_broj = sm._broj;
	_maxBrojOsoba = sm._maxBrojOsoba;
	_cijenaPoOsobi = sm._cijenaPoOsobi;
}

Smjestaj::~Smjestaj() { delete _tipSmjestaja;   _tipSmjestaja = nullptr; }

Smjestaj& Smjestaj::operator=(const Smjestaj& sm) {
	if (&sm == this)
		return *this;
	delete _tipSmjestaja;
	_tipSmjestaja = new TipSmjestaja(*sm._tipSmjestaja);
	_broj = sm._broj;
	_cijenaPoOsobi = sm._cijenaPoOsobi;
	_maxBrojOsoba = sm._maxBrojOsoba;
	return *this;
}

int Smjestaj::getBrojSmjestaja()const {return _broj;}
int Smjestaj::getMaxOsoba()const { return _maxBrojOsoba; }
double Smjestaj::getCijena()const { return _cijenaPoOsobi; }
char* Smjestaj::getTipSmjestaja()const { return (char*)TipSmjestajaString[*_tipSmjestaja]; }

void Smjestaj::setMaxOsoba(int max) {_maxBrojOsoba = max;}
void Smjestaj::setCijenaPoOsobi(double c) { _cijenaPoOsobi = c; }

ostream& operator<<(ostream& COUT, Smjestaj& sm) {
	cout << "Broj sobe: " << sm._broj << endl;
	cout << "Tip smjestaja: " << TipSmjestajaString[*sm._tipSmjestaja] << endl;
	cout << "Kapacitet smjestaja: " << sm._maxBrojOsoba <<" osoba\n";
	cout << "Cijena po osobi: " << sm._cijenaPoOsobi <<" BAM\n";
	return COUT;
}
bool operator==(const Smjestaj& s1, const Smjestaj& s2) {
	return s1._broj == s2._broj && *s1._tipSmjestaja == *s2._tipSmjestaja && s1._maxBrojOsoba == s2._maxBrojOsoba &&  s1._cijenaPoOsobi == s2._cijenaPoOsobi;
}