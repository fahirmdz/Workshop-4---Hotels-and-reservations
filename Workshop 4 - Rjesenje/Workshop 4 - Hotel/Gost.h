#pragma once
class Gost {
	char* _imePrezime;
	char* _kontaktTelefon;

public:
	Gost();
	Gost(const char*, const char*);
	Gost(Gost&);
	Gost(Gost&&);
	~Gost();

	Gost& operator=(const Gost&);

	char* getImePrezime()const;
	char* getKontaktTelefona()const;

	void setImePrezime(const char*);
	void setKontaktTelefon(const char*);

	bool valid()const;
	friend ostream& operator<<(ostream&, Gost&);
	friend bool operator==(const Gost&, const Gost&);
};