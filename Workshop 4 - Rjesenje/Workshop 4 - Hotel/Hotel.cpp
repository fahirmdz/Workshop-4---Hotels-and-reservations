#include"pch.h"

int Hotel::_stopaPDV = 20;
	Hotel::Hotel():_naziv(nullptr),_smjestaji(nullptr),_brojSmjestaja(0),_rezervacije(nullptr),_brojRezervacija(0){}

	Hotel::Hotel(const char* naziv) :_naziv(AlocirajNizKaraktera(naziv)), _smjestaji(nullptr), _brojSmjestaja(0),
		_rezervacije(nullptr), _brojRezervacija(0) {}

	Hotel::Hotel(const Hotel& hotel):_naziv(AlocirajNizKaraktera(hotel._naziv)),_brojRezervacija(hotel._brojRezervacija),_brojSmjestaja(hotel._brojSmjestaja) {
		if (_brojRezervacija > 0 && hotel._rezervacije != nullptr) {
			_rezervacije = new Rezervacija[_brojRezervacija];
			for (int i = 0; i < _brojRezervacija; i++)
				_rezervacije[i] = hotel._rezervacije[i];
		}
		else _rezervacije = nullptr;

		if (_brojSmjestaja > 0 && hotel._smjestaji != nullptr) {
			_smjestaji = new Smjestaj[_brojSmjestaja];
			for (int i = 0; i < _brojSmjestaja; i++)
				_smjestaji[i] = hotel._smjestaji[i];
		}
		else _smjestaji = nullptr;
	}
	Hotel::Hotel(Hotel&& hotel) {
		_naziv = hotel._naziv;
		hotel._naziv = nullptr;
		_brojSmjestaja = hotel._brojSmjestaja;
		_brojRezervacija = hotel._brojRezervacija;
		_smjestaji = hotel._smjestaji;
		hotel._smjestaji = nullptr;
		_rezervacije = hotel._rezervacije;
		hotel._rezervacije = nullptr;
	}
	Hotel::~Hotel() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _smjestaji; _smjestaji = nullptr;
		delete[] _rezervacije; _rezervacije = nullptr;
	}

	Hotel& Hotel::operator=(const Hotel& hotel) {
		if (&hotel == this)
			return *this;
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(hotel._naziv);
		_brojSmjestaja = hotel._brojSmjestaja;
		_brojRezervacija = hotel._brojRezervacija;
		if (_brojRezervacija > 0 && hotel._rezervacije != nullptr) {
			_rezervacije = new Rezervacija[_brojRezervacija];
			for (int i = 0; i < _brojRezervacija; i++)
				_rezervacije[i] = hotel._rezervacije[i];
		}
		else _rezervacije = nullptr;

		if (_brojSmjestaja > 0 && hotel._smjestaji != nullptr) {
			_smjestaji = new Smjestaj[_brojSmjestaja];
			for (int i = 0; i < _brojSmjestaja; i++)
				_smjestaji[i] = hotel._smjestaji[i];
		}
		else _smjestaji = nullptr;
		return *this;
	}
	Hotel& Hotel::operator+=(const Smjestaj& smjestaj){
		if(_brojSmjestaja>0)
			for(int i=0;i<_brojSmjestaja;i++)
				if (_smjestaji[i].getBrojSmjestaja() == smjestaj.getBrojSmjestaja()) {
					cout << "Smjestaj sa istim brojem vec postoji..\n";
					return *this;
				}
		Smjestaj* temp = new Smjestaj[_brojSmjestaja + 1];
			for (int i = 0; i < _brojSmjestaja; i++)
				temp[i] = _smjestaji[i];
		delete[] _smjestaji;
		_smjestaji = temp;
		_smjestaji[_brojSmjestaja++] = smjestaj;
		return *this;
	}
	bool Hotel::operator+=(const Rezervacija& rez) {
		int index = trazeniSmjestaj(rez.getSmjestaj());
		if (index == -1) {
			cout << "Trazeni smjestaj nije u ponudi hotela.. Zao nam je..\n\n";
			return false;
		}
		if (_smjestaji[index].getMaxOsoba() < rez.getBrojOsoba()) {
			cout << "Broj osoba, koji je naveden u rezervaciji, prelazi maximalan broj osoba za trazeni smjestaj! Zao name je..\n\n";
			return false;
		}
		if (!odobriSmjestaj(rez)) {
			cout << "Smjestaj je zauzet u trazenom vremenskom periodu..Zao nam je..\n\n";
			return false;
		}

		Rezervacija* temp = new Rezervacija[_brojRezervacija + 1];
		for (int i = 0; i < _brojRezervacija; i++)
			temp[i] = _rezervacije[i];
		delete[] _rezervacije;
		_rezervacije = temp;
		_rezervacije[_brojRezervacija++] = rez;
		return true;
	}
	Smjestaj* Hotel::operator[](int index) {
		if (_smjestaji == nullptr || _brojSmjestaja <= 0 || index < 0 || index >= _brojSmjestaja)
			return nullptr;
		return &_smjestaji[index];
	}
	Rezervacija* Hotel::operator()(int index) {
		if (_rezervacije == nullptr || _brojRezervacija <= 0 || index < 0 || index >= _brojRezervacija)
			return nullptr;
		return &_rezervacije[index];
	}

	int Hotel::trazeniSmjestaj(Smjestaj sm) {
		if (_brojSmjestaja <= 0)
			return -1;
		for (int i = 0; i < _brojSmjestaja; i++)
			if (_smjestaji[i] == sm)
				return i;
		return -1;
	}
	int Hotel::trazenaRezervacija(Rezervacija& rez) {
		if (_brojRezervacija <= 0)
			return -1;
		for (int i = 0; i < _brojRezervacija; i++)
			if (_rezervacije[i] == rez)
				return i;
		return -1;
	}
	int Hotel::zauzetSmjestaj(Smjestaj& sm) {
		if (_brojRezervacija <= 0 )
			return -1;
		for (int i = 0; i < _brojRezervacija; i++)
			if (sm == _rezervacije[i].getSmjestaj())
				return i;
		return -1;
	}
	bool Hotel::odobriSmjestaj(const Rezervacija& rez) {
		if (_brojSmjestaja <= 0)
			return false;
		for (int i = 0; i < _brojSmjestaja; i++) {
			int index = zauzetSmjestaj(_smjestaji[i]);
			if (index != -1 && (_rezervacije[index].getDatumKraja().suma() > rez.getDatumPocetka().suma()))
				return false;
		}
		return true;
	}
	Gost* Hotel::getSveGoste(int& brg) {
		if (_brojRezervacija <= 0)
			return nullptr;
		Gost* gosti = new Gost[_brojRezervacija];
		gosti[0] = *_rezervacije[0].getGost();
		brg++;

		for (int i = 1; i < _brojRezervacija; i++)
			for (int j = 0; j < brg; j++)
				if (!(gosti[j] == *_rezervacije[i].getGost()))
					gosti[brg++] = *_rezervacije[i].getGost();
		return gosti;
	}
	char* Hotel::getNaziv()const { return _naziv; }
	int Hotel::getBrojSmjestaja()const { return _brojSmjestaja; }
	int Hotel::getBrojRezervacija()const { return _brojRezervacija; }
	int Hotel::getStopaPDV()const { return _stopaPDV; }

	void Hotel::setNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(naziv);
	}
	void Hotel:: PotvrdiRezervaciju(Rezervacija& rez) {
		int r = trazenaRezervacija(rez);
		if (r == -1)
			return;
		_rezervacije[r].setStatus(Potvrdjena);
	}
	void Hotel::CheckIn(Rezervacija& rez) {
		int r = trazenaRezervacija(rez);
		if (r == -1)
			return;
		if (_rezervacije[r].getStatus() == Potvrdjena)
			_rezervacije[r].setStatus(BoravakUToku);
	}
	void Hotel::CheckOut(Rezervacija& rez, bool x = true) {
		int index = trazenaRezervacija(rez);
		if (index == -1) {
			cout << "Rezervacija ne postoji..\n";
			return;
		}
		double _iznos = 0;
		Smjestaj temp(rez.getSmjestaj());
		cout << "\n---------CHECK OUT-----------\n\n";
		cout << "--Informacije o vrsti smjestaja ->\n";
		cout << temp;
		_iznos = temp.getCijena();
		if (x) {
			_iznos += ((temp.getCijena()*((double)_stopaPDV / 100)));
			cout << "***PDV SE UKLJUCUJE I CIJENA SMJESTAJA IZNOSI " << _iznos << " BAM\n";
			cout << "\n--------------------------------------------\nBroj dodatnih usluga: " << rez.getBrojUsluga() << endl;
		}
		if (rez.getBrojUsluga() > 0)
			for (int i = 0; i < rez.getBrojUsluga(); i++) {
				if (x)
					rez[i]->obracunajPDV(_stopaPDV);
				_iznos += rez[i]->getCijena();
				cout << i + 1 << ". usluga -> " << *rez[i] << endl;
			}
		else
			cout << "--TRENUTNO NEMA DODATNIH USLUGA--\n\n--------------------------------------------------------------\n";
		cout << "UKUPNO ZA PLATITI: " << _iznos << " BAM\n--------HVALA NA POSJETI-------\n";
	}
	void Hotel::IspisiSlobodneSmjestaje(Datum OD, Datum DO) {
		if (_brojSmjestaja <= 0)
			return;
		for (int i = 0; i < _brojSmjestaja; i++) {
			int index = zauzetSmjestaj(_smjestaji[i]);
			if (index != -1 && (_rezervacije[index].getDatumKraja().suma() <= OD.suma())) {
				cout << _smjestaji[i] << endl << endl;
			}
			else if (index == -1)
				cout << _smjestaji[i] << endl << endl;
		}
	}

	Smjestaj* Hotel::GetNajTrazenijiSmjestaj(Datum OD, Datum DO) {
		if (_brojRezervacija <= 0 || _brojSmjestaja <= 0)
			return nullptr;
		int *_brojacRez = new int[_brojSmjestaja] {0};

		for (int i = 0; i < _brojRezervacija; i++)
			if (_rezervacije[i].getDatumPocetka().izmedju(OD, DO) && _rezervacije[i].getDatumKraja().izmedju(OD, DO))
				_brojacRez[trazeniSmjestaj(_rezervacije[i].getSmjestaj())]++;
		int max = 0;
		for (int i = 1; i < _brojSmjestaja; i++)
			if (_brojacRez[i] > _brojacRez[max])
				max = i;
		return &_smjestaji[max];
	}
	Gost* Hotel::PronadjiVIPGosta() {
		int brg = 0;
		Gost* gosti = getSveGoste(brg);
		if (gosti == nullptr)
			return nullptr;
		auto getIndexGosta = [=](Gost& g) {
			for (int i = 0; i < brg; i++)
				if (g == gosti[i])
					return i;
			return -1;
		};

		double* _utroseno = new double[brg];

		for (int i = 0; i < _brojRezervacija; i++)
			_utroseno[getIndexGosta(*_rezervacije[i].getGost())] += _rezervacije[i].getIznos();
		int max = 0;
		for (int i = 1; i < brg; i++)
			if (_utroseno[i] > _utroseno[max])
				max = i;
		return &gosti[max];
	}
	ostream& operator<<(ostream& COUT, Hotel& h) {
		if (h._naziv == nullptr)
			return COUT;
		cout << "\n====HOTEL '" << h._naziv << "'========\n";
		cout << "Broj smjestaja: " << h._brojSmjestaja << endl;
		if (h._brojSmjestaja > 0)
			for (int i = 0; i < h._brojSmjestaja; i++)
				cout << i + 1 << ". smjestaj--> " << h._smjestaji[i] << endl;
		else cout << "--TRENUTNO NEMA SMJESTAJA--\n";
		cout << "Broj rezervacija: " << h._brojRezervacija;
		cout << "\nStopa PDV-a: " << h._stopaPDV << endl << endl;
		return COUT;
	}
	bool operator==(const Hotel& h1, const Hotel& h2) {
		if (h1._naziv == nullptr || h2._naziv == nullptr)
			return false;
		return strcmp(h1._naziv, h2._naziv) == 0 && h1._brojRezervacija == h2._brojRezervacija && h1._brojSmjestaja == h2._brojSmjestaja;
	}