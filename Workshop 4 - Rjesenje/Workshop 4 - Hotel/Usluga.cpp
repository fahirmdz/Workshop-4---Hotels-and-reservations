#include"pch.h"


const char* charTipNaplate[] = { "PoOsobi", "Jednokratno", "PoNocenju" };
	Usluga::Usluga() : _naziv(nullptr), _cijena(0), _tipNaplate(TipNaplate(0)) {}

	Usluga::Usluga(const char* naziv, int cijena, TipNaplate tipNaplate) : _cijena(cijena), _tipNaplate(tipNaplate) {
		_naziv = AlocirajNizKaraktera(naziv);
	}

	Usluga::~Usluga() { delete[] _naziv;   _naziv = nullptr; }

	Usluga::Usluga(const Usluga& us):_naziv(AlocirajNizKaraktera(us._naziv)),_cijena(us._cijena),_tipNaplate(us._tipNaplate) {}
	Usluga::Usluga(Usluga&& us) {
		_naziv = us._naziv;
		us._naziv = nullptr;
		_cijena = us._cijena;
		_tipNaplate = us._tipNaplate;
	}

	Usluga& Usluga::operator=(const Usluga& us) {
		if (&us == this)
			return *this;
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(us._naziv);
		_cijena = us._cijena;
		_tipNaplate = us._tipNaplate;
		return *this;
	}

	char* Usluga::getNaziv()const {return _naziv;}
	double Usluga::getCijena()const { return _cijena; }
	char* Usluga::getTipNaplate()const { return (char*)charTipNaplate[_tipNaplate]; }

	void Usluga::setNaziv(const char* naziv) { _naziv = AlocirajNizKaraktera(naziv); }
	void Usluga::setCijenu(double cijena) { _cijena = cijena; }
	
	void Usluga::obracunajPDV(double popust) {
		_cijena -= (_cijena*(popust / 100));
	}
	ostream& operator<<(ostream& COUT, Usluga& us) {
		if (us._naziv == nullptr)
			return COUT;
		cout << "Naziv usluge: " << us._naziv << endl;
		cout << "Cijena: " << us._cijena << " BAM\n";
		cout << "\nTip naplate: " << charTipNaplate[us._tipNaplate] << endl;
		return COUT;
	}
	bool operator==(const Usluga& us1, const Usluga& us2) {
		if (us1._naziv == nullptr || us2._naziv == nullptr)
			return false;
		return strcmp(us1._naziv, us2._naziv) == 0 && us1._cijena == us2._cijena && us1._tipNaplate == us2._tipNaplate;
	}
