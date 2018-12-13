//fahirmdz GitHub

#include"pch.h"

int main() {

#pragma region Hotel 

	const int brojUsluga(5);
	Hotel hotel1("Hotel Mostar");

	Usluga* usluge[brojUsluga];
	usluge[0] = new Usluga("Parking", 5, TipNaplate(1));
	usluge[1] = new Usluga("Dorucak", 10, TipNaplate(0));
	usluge[2] = new Usluga("Rucak", 15, TipNaplate(0));
	usluge[3] = new Usluga("Wellness & SPA", 40, TipNaplate(2));
	usluge[4] = new Usluga("Veseraj", 10, TipNaplate(2));

	Smjestaj apartman(1, TipSmjestaja(0), 5, 30);
	Smjestaj soba1(2, TipSmjestaja(1), 2, 20);
	Smjestaj soba2(3, TipSmjestaja(2), 4, 20);
	Smjestaj soba3(1, TipSmjestaja(0), 2, 15);

		//Funkciju za dodavanje smjestajnih kapaciteta hotela. Hotel ne moze imati više smještaja 
		//pod istim brojem. 
		hotel1+=(apartman); 
		hotel1 += (soba1);
		hotel1 += (soba2);
		hotel1 += (soba3); //Neće se dodati radi zauzetosti broja smještaja 
	
		//Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu. 
		cout << "---LISTA SLOBODNIH SMJESTAJA U PERIODU OD 24/10/2018 - 1/11/2018-----\n\n";
		hotel1.IspisiSlobodneSmjestaje(Datum(24, 10, 2018), Datum(1, 11, 2018)); 
	
		//Ispis dodatnih usluga 
		for (int i = 0; i < brojUsluga; i++)  {
			cout<<*usluge[i] << endl;
		} 
	
	#pragma endregion 
	
	#pragma region RezervacijaGost1 
		Gost gost2("Adijan Marić", "066/111-333");
		Gost gost1("Marija Perić", "033/222-555");
		Rezervacija rezervacija1(Datum(28, 10, 2018), Datum(2, 11, 2018), gost1, apartman, 4);//Posljednji parametar konstruktora je broj osoba 
		rezervacija1+=*usluge[0]; //Parking  
		rezervacija1 += *usluge[1]; //Doručak za 3 osobe 
	
	
		//Funkcija kojom se dodaje nova rezervacija pod uslovom da smjestaj nije zauzet u trazenom periodu 
		//i da kapacitet smještaja nije manji od broja osoba. Funkcija treba da ispiše sve uslove koje rezervacija
		//ne ispunjava. 
		if (hotel1+=rezervacija1)  
			cout << "Uspjesno ste rezervisali smjestaj." << endl; 
		else   
			cout << "Rezervacija smjestaja nije uspjela." << endl; 
	
		hotel1.PotvrdiRezervaciju(rezervacija1); //Prije nego se gosti prijave u hotel rezervacija mora biti potvrđena. 
		hotel1.CheckIn(rezervacija1); //Mijenja status rezervacije na BoravakUToku, pod uslovom da je ista prethodno potvrđena. 
	
	
		/*Vrši ispis računa sa svim stavkama rezervacije (posebno stavka za smještaj, a posebno za sve usluge sa  
		pripadajućim cijenama, te ukupnim iznosom računa na kraju). Parametar tipa bool govori da li je potrebno obračunati 
		PDV po utvrđenoj stopi na ukupan iznos računa te na sve stavke pojedinačno.*/ 
		hotel1.CheckOut(rezervacija1, true);
	
	   #pragma region RezervacijaGost2 
		
		Rezervacija rezervacija2(Datum(29, 10, 2018), Datum(5, 11, 2018), gost2, apartman, 4); 

	
		if (hotel1+=rezervacija2) 
			cout << "Uspjesno ste rezervisali smjestaj." << endl; 
		else  
			cout << "Rezervacija smjestaja nije uspjela." << endl;
	
	#pragma endregion 
	
		//Pronalazi i vraća podatke o najtraženijem smještaju hotela (onaj koji je najviše puta rezervisan u datom periodu) 
		cout <<"\n------Smjestaj koji je najvise puta rezervisan----\n"<< *hotel1.GetNajTrazenijiSmjestaj(Datum(1, 1, 2018), Datum(24, 1, 2018)) << endl;
		
		//Pronalazi i ispisuje podate o VIP gostu (onaj koji je u sumi utrošio najviše novca u hotelu u trenutnoj godini - 2018). 
		cout << "\n----VIP Gost koji je utrosio najvise novca u nasem hotelu u 2018. godini----\n" << *hotel1.PronadjiVIPGosta() << endl;
	
		for (size_t i = 0; i < brojUsluga; i++) { delete usluge[i]; }
	
		system("pause");
	
		return 0;
	}
	//#pragma endregion
