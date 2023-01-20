/// @file test.cpp: előre megadott paraméterekkel minden függvényt kipróbál

#include "test.h"


bool test_main() {

	try {
		Kozpont* k1 = new Kozpont(1, 10, 10);	// létrehozunk pár példa központot és embert
		Kozpont* k2 = new Kozpont(2, 3, 1);
		Ember* e1 = new Ember("Jani", 1023, 5);
		Ember* e2 = new Ember("Bela", 1111, 2);
		Ember* e3 = new Ember("Urleny", 2000, 3);

		vector<Kozpont*> kptok = { k1, k2 };	// a központok tárolása, mint ahogyan a main() metódusban
		vector<Ember*> mbrek = { e1, e2, e3 };	// az emberek táolása, mint a main() metódusban

		try {
			dimport(&kptok, &mbrek, "kozpontok.txt", "emberek.txt");	// file-okból is beolvasunk pár központot és embert
		}
		catch (const char* exc) {
			cerror(exc);

		}


		try {
			k1->call(1023, 1111, &kptok, &mbrek);	// A tesztelő ne fejezze be a kapcsolatot, automatikusan fog küldeni egy üzenetet!
		}
		catch (const char* exc)
		{
			cerror(exc);
		}

		try {
			k1->call(1023, 1111, &kptok, &mbrek);	// Kipróbáljuk a már létező kapcsolathoz való csatlakozást, majd pedig fejezze be a kapcsolatot! Ekkor a hívott félnek be fog telni a tárhelye.
		}
		catch (const char* exc)
		{
			cerror(exc);
		}

		try {
			k1->call(1023, 2000, &kptok, &mbrek);		// Újabb hívás, mivel az előzőt befejeztük, ezért a hívó fél nem lesz foglalt már. Még ne zárjuk be, hogy legyen nyitott kapcsolat az 1-es központban!
		}
		catch (const char* exc)
		{
			cerror(exc);

		}

		try {
			k1->kapcsolatok();	// Kiírja a k1  központban tárolt 1 darab kapcsolat és a központ adatait.
		}
		catch (const char* exc)
		{
			cerror(exc);

		}

		try {
			k1->call(1023, 2000, &kptok, &mbrek);	// Újra csatlakozunk az előbbi kapcsolatunkhoz, befejezhetjük akár, ha nem, akkor majd a központ törlésénél fog befejeződni.
		}
		catch (const char* exc)
		{
			cerror(exc);

		}

		try {
			e1->uzenetek();	// Itt megnézzük a 3 példa ember üzeneteit, lehet törölni is akár őket, vagy nem.
			e2->uzenetek();
			e3->uzenetek();
		}
		catch (const char* exc)
		{
			cerror(exc);

		}
		try {
			dexport(&kptok, &mbrek);
		}
		catch (const char* exc) {
			cerror(exc);
		}

		for (size_t i = 0; i < kptok.size();i++)
		{
			delete kptok[i];	// Felszabadítjuk a dinamikusan lefoglalt központokat, ugyanez megtörténne a main() függvényben is
		}
		for (size_t i = 0; i < mbrek.size();i++)
		{
			delete mbrek[i];	// Felszabadítjuk a dinamikusan lefoglalt embereket, a main()-ben is megtesszük ugyanezt
		}

		return true;
	}
	catch (...)
	{
		return false;	// Ha másmilyen kivételt dobna a tesztelés, mint amilyet vártunk, akkor azt itt kapjuk el. Egy hamis visszatéréssel jelezzük, hogy hiba van valószínűleg a programban.
	}
}
