/// @file kapcstabla.cpp: tartalmazza a Tabla osztály függvényeinek a megvalósítását

#include "kapcstabla.h"

/// <summary>
/// Hozzáad egy új kapcsolatot a táblába, ha lehet,
/// const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="kapcs">a táblához adandó kapcsolat pointere, a kapcsolatot a központ hozza létre</param>
/// <param name="belso">megmondja, hogy belső kapcsolatról van-szó</param>
void Tabla::add(Kapcsolat* kapcs, bool belso) {
	if (belso)
	{
		if (indb < maxbe)
		{
			for (size_t i = 0; i < maxki + maxbe;i++)
			{
				if (adatok[i] == NULL) {
					adatok[i] = kapcs;
					indb++;
					return;
				}
			}
			throw  "Nyilvantartasi hiba, nincs tobb hely!";
		}
		else
		{
			delete kapcs;
			throw "Nincs tobb hely belso kapcsolasra!";
		}
	}
	else
	{
		if (outdb < maxki)
		{
			for (size_t i = 0; i < maxki + maxbe;i++)
			{
				if (adatok[i] == NULL) {
					adatok[i] = kapcs;
					outdb++;
					return;
				}
			}
			throw "Nyilvantartasi hiba, nincs tobb hely!";
		}
		else
		{
			delete kapcs;
			throw "Nincs tobb hely kulso kapcsolasra";
		}
	}
}

/// <summary>
/// Megszűntet egy kapcsolatot,
/// const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="id">a kapcsolat azonosítója</param>
void Tabla::remove(int id) {
	for (size_t i = 0; i < maxbe + maxki;i++) {
		if (adatok[i]->getid() == id) {
			try {
				delete adatok[i];
				adatok[i] = NULL;

				if (id / 10000000 == korzet)
					indb--;

				else
					outdb--;

				return;
			}
			catch (const char*) {
				adatok[i] = NULL;

				if (id / 10000000 == korzet)
					indb--;

				else
					outdb--;
				throw;
			}
			
		}
	}
	throw "Nem talaltunk ilyen azonositoju kapcsolatot a kapcsolotablaban.";
}

/// <summary>
/// A tábla tartalmának megtekintése
/// </summary>
void Tabla::check() const {
	std::cout << "A kapcsolotablaban tarolt kapcsolatok:\n" << std::endl;
	for (size_t i = 0; i < maxbe + maxki;i++)
	{
		if (adatok[i] != NULL) {
			std::cout <<adatok[i];
		}
	}
	std::cout << "	Szabad belso kapcsolathelyek szama: " << maxbe - indb << "\n	Szabad kulso kapcsolathelyek szama: " << maxki - outdb << std::endl;
}

/// <summary>
/// Megmondja, hogy a tábla tartalmazza-e az adott azonosítójú kapcsolatot
/// </summary>
/// <param name="id">a kapcsolat azonosítója</param>
/// <returns>tartalmazza-e</returns>
bool Tabla::contains(int id) const {
	for (size_t i = 0; i < maxbe + maxki; i++)
	{
		if (adatok[i] != NULL)
			if(adatok[i]->getid() == id)
				return true;
	}
	return false;
}

/// <summary>
/// Egy megadott id alapjan megkeresi es visszater az adott kapcsolat pointerevel, vagy NULL-lal
/// </summary>
/// <param name="id">a kapcsolat azonosítója</param>
/// <returns>a keresett kapcsolatra mutató pointer</returns>
Kapcsolat* Tabla::idtokapcs(int id)const {
	for (size_t i = 0; i < maxbe + maxki; i++)
	{
		if (adatok[i]->getid() == id)
			return adatok[i];
	}
	return NULL;
}