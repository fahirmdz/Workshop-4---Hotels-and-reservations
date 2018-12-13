#include"pch.h"



   //Constructors and destructor
Gost::Gost():_imePrezime(nullptr),_kontaktTelefon(nullptr){}
	Gost::Gost(const char* imePrezime, const char* kontaktTelefon) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_kontaktTelefon = AlocirajNizKaraktera(kontaktTelefon);
	}


	Gost::Gost(Gost& gs):_imePrezime(AlocirajNizKaraktera(gs._imePrezime)),_kontaktTelefon(AlocirajNizKaraktera(gs._kontaktTelefon)) {}

	Gost::Gost(Gost&& gs) {
		_imePrezime = gs._imePrezime;
		_kontaktTelefon = gs._kontaktTelefon;
		gs._imePrezime = gs._kontaktTelefon = nullptr;
	}
	Gost::~Gost() {
		delete[] _imePrezime;
		delete[] _kontaktTelefon;
		_imePrezime = _kontaktTelefon = nullptr;
	}

	//Get methods
	char* Gost::getImePrezime()const {
		return _imePrezime;
	}
	char* Gost::getKontaktTelefona()const {
		return _kontaktTelefon;
	}

	//Set methods
	void Gost::setImePrezime(const char* imePrezime) {
		if (imePrezime == nullptr)
			return;
		delete[] _imePrezime;
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	void Gost::setKontaktTelefon(const char* telefon) {
		if (telefon == nullptr)
			return;
		delete[] _kontaktTelefon;
		_kontaktTelefon = AlocirajNizKaraktera(telefon);
	}

	//Operators
	Gost& Gost::operator=(const Gost& gs) {
		if (&gs == this)
			return *this;
		delete[] _kontaktTelefon;
		delete[] _imePrezime;
		_imePrezime = AlocirajNizKaraktera(gs._imePrezime);
		_kontaktTelefon = AlocirajNizKaraktera(gs._kontaktTelefon);
		return *this;
	}

	bool Gost::valid()const{ return _imePrezime != nullptr && _kontaktTelefon != nullptr; }
	ostream& operator<<(ostream& COUT, Gost& gs) {
		if (!gs.valid())
			return COUT;
		cout << "Ime i prezime: " << gs._imePrezime << endl;
		cout << "Kontakt telefon: " << gs._kontaktTelefon << endl;
		return COUT;
	}

	bool operator==(const Gost& gs1, const Gost& gs2) {
		if (!gs1.valid() || !gs2.valid())
			return false;
		return strcmp(gs1._imePrezime, gs2._imePrezime) == 0 && strcmp(gs2._kontaktTelefon, gs1._kontaktTelefon) == 0;
	}