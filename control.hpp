/// @file control.hpp: ez tartalmazza a main() által meghívott vezérlő függvényeket

// ReSharper disable CppClangTidyCertErr60Cpp
// ReSharper disable CppClangTidyMiscThrowByValueCatchByReference
// ReSharper disable CppDeprecatedEntity
#pragma once

#include <iostream>
#include <fstream>
#include "kozpont.h"
#include "ember.h"
#include <vector>
// ReSharper disable once CppUnusedIncludeDirective
#include "gtest_lite.h"
#include "memtrace.h"

using std::string;
using std::ifstream;

/// <summary>
/// A vezérlő szekcióban egységes hibakiíró függvény.
/// </summary>
/// <param name="exc">const char* kivétel</param>
inline void cerror(const char* exc)
{
	cerr << "\n^^" << exc << "^^" << endl;
}

/// <summary>
/// Egységes hibaüzenet a hasonló típusú hibákhoz.
/// </summary>
// ReSharper disable once IdentifierTypo
static string errstr = "Rosszul adta meg a parametereket, vagy nem adott meg semmit :(.";  // NOLINT(clang-diagnostic-exit-time-destructors)

/// <summary>
/// Új központ hozzáadása a standard inputról.
/// </summary>
/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
inline void addnkp(vector<Kozpont*>* kozpontok) {
	cout << "	Adja meg a kozpont korzetszamat! (1-9): ";
	int k = 0;
	cin >> k;
	if (cin.eof())
		throw "Ctrl Z";
	cout << "	Adja meg a kozpontban letrehozhato belso kapcsolatok maximalis szamat! (lehet 0 is): ";
	int in = -1;
	cin >> in;
	if (cin.eof())
		throw "Ctrl Z";
	cout << "	Adja meg a kozpontban letrehozhato kulso kapcsolatok maximalis szamat! (lehet 0 is): ";
	int out = -1;
	cin >> out;
	if (cin.eof())
		throw "Ctrl Z";


	for (size_t i = 0; i < kozpontok->size(); i++)
	{
		if (kozpontok->at(i)->getkorzet() == k)
		{
			throw "Van mar ilyen korzetszamu kozpont az adatbazisban.";
		}
	}

	if (k > 0 && k < 10 && in >= 0 && out >= 0) {
		Kozpont* uj = new Kozpont(k, in, out);
		kozpontok->push_back(uj);
		return;
	}
	else
	{
		throw errstr;
	}
}

/// <summary>
/// Új ember hozzáadása a standard inputról.
/// </summary>
/// <param name="emberek">az embereket tároló vektorra mutató pointer</param>
/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
inline void addnmbr(vector<Ember*>* emberek, vector<Kozpont*>* kozpontok) {
	cout << "	Adja meg az elofizeto nevet!: ";
	string nev = "";
	cin.ignore();
	cp::getline(cin, nev);
	if (cin.eof())
		throw "Ctrl Z";
	cout << "	Adja meg " << nev << " telefonszamat! (4 jegyu, nem 0-val kezdodo, csak mar letezo kozponthoz tartozo telefonszamot adhat meg): ";
	int tel = 0;
	cin >> tel;
	if (cin.eof())
		throw "Ctrl Z";
	cout << "	Adja meg az elofizeto uzenettarhelyenek a meretet!: ";
	unsigned int tar = 10;
	cin >> tar;

	if (cin.eof() || cin.fail() || cin.bad())
		cin.clear();


	bool valostel = false;

	for (size_t i = 0; i < kozpontok->size(); i++) {
		if (tel / 1000 == kozpontok->at(i)->getkorzet())
			valostel = true;
	}
	if (!valostel) {

		throw "Nem letezo kozponthoz tartozo telefonszamot szeretett volna letrehozni.";
	}
	for (size_t i = 0; i < emberek->size(); i++) {
		if ((int) emberek->at(i)->gettel() == tel)
		{
			throw "Van mar ilyen telefonszamu ember az adatbazisban.";
		}
	}

	if (nev != "" && tel > 999 && tel < 10000) {
		Ember* uj = new Ember(nev, tel, tar);
		emberek->push_back(uj);
		return;
	}
	else
	{
		throw  errstr;
	}
}

/// <summary>
/// Hívást / kapcsolatkezelést vezérlő függvény.
/// </summary>
/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
/// <param name="emberek">az embereket tároló vektorra mutató pointer</param>
inline void maincall(vector<Kozpont*>* kozpontok, vector<Ember*>* emberek) {
	cout << "	Adja meg a telefonszamat!: ";
	int hivo = 0;
	cin >> hivo;
	if (cin.eof())
		throw "Ctrl Z";
	cout << "	Adja meg a hivott fel telefonszamat!: ";
	int cel = 0;
	cin >> cel;
	if (cin.eof())
		throw "Ctrl Z";

	for (size_t i = 0; i < kozpontok->size(); i++) {
		if (kozpontok->at(i)->getkorzet() == hivo / 1000)
		{
			kozpontok->at(i)->call(hivo, cel, kozpontok, emberek);
			return;
		}
	}
	throw "Nem talaltuk meg a hivo fel kozpontjat. Ugy nez ki, hogy nem letezik.";
}

/// <summary>
/// Az üzenetek megtekintését vezérlő függvény.
/// </summary>
/// <param name="emberek">az embereket tároló vektorra mutató pointer</param>
inline void login(vector<Ember*>* emberek) {
	cout << "	Adja meg a telefonszamat: ";
	int tel = 0;
	cin >> tel;
	if (cin.eof())
		throw "Ctrl Z";

	for (size_t i = 0; i < emberek->size(); i++) {
		if ((int) emberek->at(i)->gettel() == tel) {
			emberek->at(i)->uzenetek();

			cout << "	Remeljuk elegedett a szolgaltatasunkkal." << endl;
			return;
		}
	}

	throw "Nem talaltuk a telefonszammat, probalja ujra kesobb!";
}

/// <summary>
/// Egy adott központtól való adatigénylést vezérlő függvény
/// </summary>
/// <param name="kozpontok"></param>
inline void kozpinfo(vector<Kozpont*>* kozpontok) {
	cout << "	Adja meg a kozpont korzetszamat, mely utan erdeklodik!: ";
	int k = 0;
	cin >> k;

	if (k <= 0 || k > 9) {
		throw errstr;
	}

	for (size_t i = 0; i < kozpontok->size(); i++) {
		if (kozpontok->at(i)->getkorzet() == k) {
			kozpontok->at(i)->kapcsolatok();
			return;
		}
	}
	throw "Nem talaltuk meg a megadott kozpontot.";
}

/// <summary>
/// Központok és emberek file-ból való importálása
/// </summary>
/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
/// <param name="emberek">az embereket tároló vektorra mutató pointer</param>
/// <param name="kpath">a központokat tartalmazó file neve és elérési útvonala, ha nincs megadva, akkor a standard inputon keresztül kell majd megadni</param>
/// <param name="epath">az embereket tartalmazó file neve és elérési útvonala, ha nincs megadva, akkor a standard inputon keresztül kell majd megadni</param>
inline void dimport(vector<Kozpont*>* kozpontok, vector<Ember*>* emberek, string kpath = "", string epath = "") {
	cout << R"(
Eloszor lehetosege van kozpontokat beolvasni file-bol, kesobb majd embereket is.
Felhivom a figyelmet arra, hogy az adott kozpont csak akkor lesz felveve az adatbazisba, hogyha meg nem tarolunk olyan korzetszamut(1-9).
A kozpontok megkovetelt formatuma a file-on belul a kovetkezo:
//*.txt
{korzetszam - int (1-9)} + {szokoz} + {maximalis belso kapcsolatok szama - int} + {szokoz} + {maximalis kulso kapcsolatok szama - int}	-> ez egy darab kozpont
... -> egy masik kozpont
...

Adja meg az importalando kozpontokat tartalmazo .txt kiterjesztesu file eleresi utvonalat!:)" << endl;

	if (kpath == "") {
		cin.ignore();
		cp::getline(cin, kpath);
	}
	ifstream in(kpath);

	if (!in) {
		throw "Rossz eleresi utat adott meg a kozpontokhoz.";
	}

	int cnt = 0;
	while (!in.eof()) {
		int k = 0;
		int i = 0;
		int o = 0;
		in >> k >> i >> o;
		bool uj = true;

		for (size_t j = 0; j < kozpontok->size(); j++)
		{
			if (kozpontok->at(j)->getkorzet() == k)
			{
				uj = false;
			}
		}
		if (uj) {
			if ((k > 0) && (k < 10)) {
				Kozpont* kuj = new Kozpont(k, i, o);
				kozpontok->push_back(kuj);
				cnt++;
			}
			else {
				throw "Hianyos / rossz formatumu a kozpontokat tartalmazo file.";
			}
		}
	}
	in.close();

	cout << "\nSikeresen hozzaadott " << cnt << " uj kozpontot.\n" << R"(
Most lehetosege lesz embereket is hozzaadni az adatbazishoz.
Felhivom a figyelmet arra, hogy ha mar nyilvantartunk adott telefonszamu embert, akkor ujat azon a szamon nem veszunk fel, tovabba nem letezo kozponthoz tartozo telefonszaut se.
Az elofizetok megkovetelt formatuma a file-on belul a kovetkezo:
//*.txt
{1. ember neve - string (max 50 karakter szokozzel)}
{1. ember telefonszama - int (1000-9999)}
{1. ember uzeneteinek a terhelyenek a merete - int}
{2. ember ...}

Adja meg az importalando embereket tartalmazo .txt kiterjesztesu file eleresi utvonalat, szokozmentesen!:)" << endl;
	if (epath == "")
	{
		cp::getline(cin, epath);
	}

	in.open(epath);

	if (!in) {
		throw "Rossz eleresi utat adott meg az emberekhez.";
	}

	cnt = 0;
	while (!in.eof()) {
		string nev = "";
		int tel = 0;
		int meret = 0;
		bool uj = true;

		try {

			if (getline(in, nev))
			{
				if (nev.size() && *nev.rbegin() == '\r')
					nev.erase(nev.size() - 1);
				in >> tel;
				in >> meret;
				in.ignore();
			}
			else {
				throw "Nem sikerult beolvasni az embereket tartalmazo file-t.";
			}
		}
		catch (const char*)
		{
			throw;
		}

		bool valostel = false;

		for (size_t i = 0; i < kozpontok->size(); i++) {
			if (tel / 1000 == kozpontok->at(i)->getkorzet())
				valostel = true;
		}
		if (valostel) {

			for (size_t i = 0; i < emberek->size(); i++) {
				if ((int) emberek->at(i)->gettel() == tel)
				{
					uj = false;
					break;
				}
			}

			if ((nev != "") && (tel > 999) && (tel < 10000) && uj) {
				Ember* ember = new Ember(nev, tel, meret);
				emberek->push_back(ember);
				cnt++;
			}
		}
	}
	in.close();
	cout << "\nSikeresen hozzaadott " << cnt << " uj embert:\n" << endl;
	for (size_t i = 0; i < emberek->size();i++) {
		cout << "\n - " << emberek->at(i) << "\n";
	}

	return;

}

/// <summary>
/// A központok és az emberek exportálása 1-1 .txt file-ba.
/// </summary>
/// <param name="kozpontok">A központokat tartalmazó vektorra mutató pointer.</param>
/// <param name="emberek">Az embereket tartalmazó vektorra mutató pointer.</param>
inline void dexport(vector<Kozpont*>* kozpontok, vector<Ember*>* emberek) {
	cout << R"(
	A kozpontok es az emberek a program gyokermappajaba lesznek irva, expkozpontok.txt es expemberek.txt neven.
)" << endl;

	std::ofstream os("expkozpontok.txt");

	if (!os) {
		throw "Nem sikerult letrehozni a kozpontok exportalasi dokumentumat.";
	}

	for (size_t i = 0; i < kozpontok->size();i++)
	{
		os << "A kozpont korzetszama: " << kozpontok->at(i)->getkorzet() << ", a maximmalis belso kapcsolatok szama: " << kozpontok->at(i)->getmaxbe() << ", a maximalis kulso kapcsolatok szama: " << kozpontok->at(i)->getmaxki() << endl;
	}

	os.close();
	os.open("expemberek.txt");

	if (!os) {
		throw "Nem sikerult letrehozni az emberek exportalasi dokumentumat.";
	}

	for (size_t i = 0; i < emberek->size(); i++) {
		os << emberek->at(i) << endl;
	}

	os.close();

	cout << "	Sikeresen exportalta a kozpontok es az emberek adatait.";
}