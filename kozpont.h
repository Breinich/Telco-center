/// @file kozpont.h: tartalmazza a Kozpont osztály függvényeinek a deklarációit, valamint a getline függvény cross-platform megvalósítását

#pragma once

//#define TESZT


#include "kapcsolat.h"
#include "kapcstabla.h"
#include "ember.h"
#include <iostream>
#include <vector>
#include <string>
#include "memtrace.h"

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::cerr;
using std::endl;

/// cross-platform getline
struct cp {      
	
	/// <summary>  // NOLINT(clang-diagnostic-documentation-unknown-command)
	/// Beolvas egy adott bemeneti folyamról egy sort egy adott string-be, majd ha szükség van rá, a stringből kiszedi a \r karaktert
	/// </summary>
	/// <param name="is">bemeneti folyam</param>
	/// <param name="str">cél string</param>
	/// <returns>bemeneti folyam</returns>
	static std::istream& getline(std::istream& is, std::string& str) {
		std::getline(is, str);
		if (str.size() && *str.rbegin() == '\r')
			str.erase(str.size() - 1);
		return is;
	}
};



class Tabla;

/// <summary>
/// Kapcsolatok tárolására és kezelésére szolgál. Tartalmaz egy Tabla objektumot, melyben a Kapcsolat objektumok tárolva vannak, továbbá a körzetszámát.
/// </summary>
class Kozpont {
	int korzet;	///< körzetszám, 1-9
	Tabla ktabla;	///< itt tárolja a kapcsolataira mutató pointereket
	

public:

	/// <summary>
	/// Létrehoz egy Tabla objektumot a megadott paraméterekkel és beállítja a körzetszámot.
	/// </summary>
	/// <param name="k">körzetszám</param>
	/// <param name="i">belső kapcsolatok max száma</param>
	/// <param name="o">külső kapcsolatok max száma</param>
	Kozpont(int k = -1, int i=0, int o=0): korzet(k), ktabla(i, o, k) {}

	/// <summary>
	/// Híváskezdeményezés,
	/// const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="hivo">A hívó telefonszáma</param>
	/// <param name="cel">A hívott telefonszáma</param>
	/// <param name="kozpontok">A központok tárolójának a pointere</param>
	/// <param name="emberek">Az emberek tárolójának a pointere</param>
	void call(int hivo, int cel, vector<Kozpont*> *kozpontok, vector<Ember*> *emberek);

	/// <summary>
	/// Vele lehet megtekinteni az éppen fennálló kapcsolatait a központnak és létrehozni új kapcsolatot
	/// </summary>
	void kapcsolatok() const;

	/// <summary>
	/// </summary>
	/// <returns>Körzetszám</returns>
	int getkorzet() const { return korzet; }
	
	/// <summary>
	/// </summary>
	/// <returns>A belső kapcsolatok maximális számma.</returns>
	int getmaxbe() const { return ktabla.getmaxbe(); }

	/// <summary>
	/// </summary>
	/// <returns>A maximális külső kapcsolatok száma.</returns>
	int getmaxki() const { return ktabla.getmaxki(); }

	/// <summary>
	/// Gondoskodik a kapcsolaton belüli üzenetküldés vezérléséről
	/// </summary>
	/// <param name="uj">A kapcsolatra mutató pointer</param>
	void uzenetkuldes(Kapcsolat* uj) const;

	/// <summary>
	/// Gondoskodik a kapcsolat befejezésének az eldöntéséről
	/// </summary>
	/// <param name="id">a kapcsolat azonosítója</param>
	/// <param name="ck">a hívott fél körzete</param>
	/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
	void befejeze(int id, int ck, vector<Kozpont*>* kozpontok);

	/// <summary>
	/// Kapcsol egy távolsági hívást,
	/// const char* kivételt dob, ha sikertelen volt
	/// </summary>
	/// <param name="hivo">a hívó emberre mutató pointer</param>
	/// <param name="cel">a hívott emberre mutató pointer</param>
	/// <param name="id">a kapcsolat leendő azonosítója</param>
	void connect(Ember* hivo, Ember* cel, int id);
	
	/// <summary>
	/// Egy kapcsolat megszűntetése és törlése a kapcsolótáblából, a kapcsolatot es a pointerét mindig a hívó ügyfél központja törölje.
	/// Const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="azon">A kapcsolat azonosítószáma</param>
	void end(int azon);

	/// <summary>
	/// </summary>
	~Kozpont() {}
};