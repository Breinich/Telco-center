/// @file kapcstabla.h: tartalmazza a Tabla osztály függvényeinek deklarációit

#pragma once
#include "kapcsolat.h"
#include "memtrace.h"


class Kapcsolat;

/// <summary>
/// Kapcsolat objektumokra mutató pointereket tárol egy véges tömbben.
/// Ezen kívül tartalmazza a hozzá tartozó központ körzetszámát és számon tartja a maximális és az aktuális kapcsolatok számát.
/// </summary>
class Tabla {
	Kapcsolat** adatok;	///< kapcsolatok tömbje
	unsigned int maxbe; ///< tároló mérete belső kapcsolóknak
	unsigned int maxki; ///< tároló mérete külső kapcsolóknak
	unsigned int indb;	///< belső kapcsolatok darabszáma
	unsigned int outdb;	///< külső kapcsolatok darabszáma
	int korzet;	///< a központjának a körzetszáma

public:

	/// <summary>
	/// Létrehozza a Kapcsolat -ok pointereinek a tömbjét és inicializálja NULL pointerekkel.
	/// </summary>
	/// <param name="b">a létrehozandó tábla belső maximális kapcolatszáma</param>
	/// <param name="k">a létrehozandó tábla külső maximális kapcolatszáma</param>
	Tabla(int b, int k, int korzet) : maxbe(b), maxki(k), indb(0), outdb(0), korzet(korzet)
	{ 
		adatok = new Kapcsolat * [b + k];
		for (int i = 0; i < b + k;i++)
			adatok[i] = NULL;
	}

	/// <summary>
	/// Hozzáad egy új kapcsolatot a táblába, ha lehet,
	/// const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="kapcs">a táblához adandó kapcsolat pointere, a kapcsolatot a központ hozza létre</param>
	/// <param name="belso">megmondja, hogy belső kapcsolatról van-szó</param>
	void add(Kapcsolat* kapcs, bool belso);

	/// <summary>
	/// Megszűntet egy kapcsolatot,
	/// const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="id">a kapcsolat azonosítója</param>
	void remove(int id);

	/// <summary>
	/// Megmondja, hogy a tábla tartalmazza-e az adott azonosítójú kapcsolatot
	/// </summary>
	/// <param name="id">a kapcsolat azonosítója</param>
	/// <returns>tartalmazza-e</returns>
	bool contains(int id) const;

	/// <summary>
	/// </summary>
	/// <returns>A maximális belső kapcsolatok száma.</returns>
	int getmaxbe() const { return maxbe; }

	/// <summary>
	/// </summary>
	/// <returns>A maximális külső kapcsolatok száma.</returns>
	int getmaxki() const { return maxki; }

	/// <summary>
	/// A tábla tartalmának megtekintése
	/// </summary>
	void check() const;

	/// <summary>
	/// Egy megadott id alapjan megkeresi es visszater az adott kapcsolat pointerevel, vagy NULL-lal
	/// </summary>
	/// <param name="id">a kapcsolat azonosítója</param>
	/// <returns>a keresett kapcsolatra mutató pointer</returns>
	Kapcsolat* idtokapcs(int id)const;

	/// <summary>
	/// Felszabadítja a Kapcsolat pointereket, majd törli a tömböt.
	/// </summary>
	~Tabla()
	{
		for (size_t i = 0; i < maxbe + maxki; i++)
		{
			if (adatok[i] != NULL) {
				delete adatok[i];
				adatok[i] = NULL;
			}
		}
		delete[] adatok;
	}
};