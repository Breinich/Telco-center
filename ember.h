/// @file ember.h: tartalmazza az Ember osztály függvényeinek deklarációit

#pragma once
#include <iostream>
#include "memtrace.h"

/// <summary>
/// Egy előfizető személy adatait tárolja: 
/// A nevét; az üzeneteit egy véges tömbben, melyek közül számon tartja, hogy mennyi olvasatlan; a telefonszámát; és a foglaltsági státuszát.
/// </summary>
class Ember {
	std::string nev;
	std::string* tarhely;
	unsigned int maxmsg;
	unsigned int telszam;
	unsigned int olvasatlan;
	bool foglalt;	

public:

	/// <summary>
	/// Mindent 0-val vagy NULL-lal inicializál.
	/// </summary>
	Ember(): nev(""), maxmsg(0), telszam(0), olvasatlan(0), foglalt(false) {	tarhely = NULL; }

	/// <summary>
	/// Lefoglalja a megadott méretű üzenettárhelyet és beállítja a többi tagváltozót is.
	/// </summary>
	/// <param name="n">név</param>
	/// <param name="tel">telefonszám - négyjegyű</param>
	/// <param name="max">üzenettárhely mérete, alapértelmezetten 10</param>
	Ember(std::string n, int tel, unsigned int max);

	/// <summary>
	/// Üzenet fogadása a fennálló kapcsolaton keresztül.
	/// Const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="msg">A fogadott üzenet</param>
	void recieve(std::string msg);

	/// <summary>
	/// Beállítja a foglalt változó értékét, ha kapcsolatba kerül az adott ember valakivel
	/// </summary>
	/// <param name="b">Foglalt legyen-e, vagy se?</param>
	void setfoglalt(bool b) { foglalt = b; }

	/// <summary>
	/// </summary>
	/// <returns>foglalt-e</returns>
	bool foglalte()const { return foglalt; }

	/// <summary>
	/// </summary>
	/// <returns>Telefonszám</returns>
	unsigned int gettel() const { return telszam; }

	/// <summary>
	/// Az üzenetek kezelése / olvasása, törlése.
	/// </summary>
	void uzenetek();

	/// <summary>
	/// Felszabadítja az üzenetek tárhelyét.
	/// </summary>
	~Ember() { if(tarhely != NULL) delete[] tarhely; }

	friend std::ostream& operator<<(std::ostream& os, const Ember* e) {
		return os << "Nev: " << e->nev << ", telefonszam: " << e->telszam;
	}
	
};