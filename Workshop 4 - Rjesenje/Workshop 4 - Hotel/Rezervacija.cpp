#include"pch.h"

const char* charStatusRezervacije[] = { "Aktivna", "Potvrdjena", "BoravakUToku", "Otkazana" };
Rezervacija::Rezervacija():_brojOsoba(0),_brojUsluga(0),_gost(nullptr),_usluge(nullptr){}

Rezervacija::Rezervacija(Datum pocetak, Datum kraj,Gost& gost, Smjestaj& smjestaj, int brojO) : _pocetakBoravka(pocetak),
_krajBoravka(kraj), _gost(new Gost(gost)), _smjestaj(smjestaj), _brojOsoba(brojO), _brojUsluga(0),_usluge(nullptr),_status(Aktivna) {
	_ukupanIznos = _brojOsoba * smjestaj.getCijena();
}

Rezervacija::Rezervacija(const Rezervacija& rez) : _pocetakBoravka(rez._pocetakBoravka),
_krajBoravka(rez._krajBoravka), _gost(new Gost(*rez._gost)), _smjestaj(rez._smjestaj), _brojOsoba(rez._brojOsoba),
_brojUsluga(rez._brojUsluga), _status(rez._status) {
	if (_brojUsluga > 0) {
		_usluge = new Usluga[_brojUsluga];
		for (int i = 0; i < _brojUsluga; i++)
			_usluge[i] = rez._usluge[i];
	}
	else _usluge = nullptr;
}

Rezervacija::Rezervacija(Rezervacija&& rez) {
	_gost = rez._gost;
	rez._gost = nullptr;
	_usluge = rez._usluge;
	rez._usluge = nullptr;
	_smjestaj = rez._smjestaj;
	_pocetakBoravka = rez._pocetakBoravka;
	_krajBoravka = rez._krajBoravka;
	_brojOsoba = rez._brojOsoba;
	_brojUsluga = rez._brojUsluga;
	_status = rez._status;
}
Rezervacija::~Rezervacija(){
	delete _gost;
	_gost = nullptr;
	if (_usluge != nullptr && _brojUsluga > 0)
		delete[] _usluge;
	_usluge = nullptr;
}

Rezervacija& Rezervacija::operator=(const Rezervacija& rez) {
	delete _gost;
	delete[] _usluge;
	_gost = new Gost(*rez._gost);
	_brojUsluga = rez._brojUsluga;
	_brojOsoba = rez._brojOsoba;

	if (_brojUsluga > 0 && rez._usluge != nullptr) {
		_usluge = new Usluga[_brojUsluga];
		for (int i = 0; i < _brojUsluga; i++)
			_usluge[i] = rez._usluge[i];
	}
	else _usluge = nullptr;
	_smjestaj = rez._smjestaj;
	_pocetakBoravka = rez._pocetakBoravka;
	_krajBoravka = rez._krajBoravka;
	_status = rez._status;
	return *this;
}
Rezervacija& Rezervacija::operator+=(const Usluga& us) {
	if (us.getNaziv() == nullptr)
		return *this;
	Usluga* temp = new Usluga[_brojUsluga + 1];

	if (_brojOsoba > 0)
		for (int i = 0; i < _brojUsluga; i++)
			temp[i] = _usluge[i];

	delete[] _usluge;   _usluge = temp;
	_usluge[_brojUsluga++] = us;
	_ukupanIznos += us.getCijena();
	cout << "Uspjesno dodana usluga..\n";
	return *this;
}
Usluga* Rezervacija::operator[](int index) {
	if (_usluge == nullptr || _brojUsluga <= 0 || index < 0 || index >= _brojUsluga)
		return nullptr;
	return &_usluge[index];
}

Datum Rezervacija::getDatumPocetka()const { return _pocetakBoravka; }
Datum Rezervacija::getDatumKraja()const { return _krajBoravka; }

Gost* Rezervacija::getGost()const {	return _gost;}
Smjestaj Rezervacija::getSmjestaj()const { return _smjestaj; }
int Rezervacija::getBrojOsoba()const {return _brojOsoba;}
int Rezervacija::getBrojUsluga()const {return _brojUsluga;}
double Rezervacija::getIznos()const {	return _ukupanIznos;}

char* Rezervacija::getStatusChar()const {	return (char*)charStatusRezervacije[_status];}
StatusRezervacije Rezervacija::getStatus()const { return _status; }
void Rezervacija::setStatus(StatusRezervacije s) {_status = s;}

ostream& operator<<(ostream& COUT, Rezervacija& rez) {
	if (rez._gost == nullptr)
		return COUT;
	cout << "--Podaci o gostu koji je napravio rezervaciju--\n";
	cout << *rez._gost << endl;
	cout << "Pocetak boravka: " << rez._pocetakBoravka << endl;
	cout << "Kraj boravka; " << rez._krajBoravka;
	cout << "\n--Podaci o smjestaju--\n" << rez._smjestaj << endl;
	cout << "Broj osoba: " << rez._brojOsoba;
	cout << "\nBroj usluga: " << rez._brojUsluga << endl;
	if (rez._brojUsluga > 0)
		for (int i = 0; i < rez._brojUsluga; i++)
			cout << i + 1 << ". usluga --> " << rez._usluge << endl;
	else cout << "--TRENUTNO NEMA DODATNIH USLUGA--\n";
	cout << "Status rezervacije: " << charStatusRezervacije[rez._status];
	cout << "\nIZNOS: " << rez._ukupanIznos << endl << endl;
	return COUT;
}
bool operator==(const Rezervacija& rez1, const Rezervacija& rez2) {
	return *rez1._gost == *rez2._gost && rez1._pocetakBoravka == rez2._pocetakBoravka && rez1._krajBoravka == rez2._krajBoravka && rez1._brojOsoba == rez2._brojOsoba;
}
