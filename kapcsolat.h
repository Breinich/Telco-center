/// @file kapcsolat.h: tartalmazza a Kapcsolat osztály függvényeinek deklarációit

#pragma once



#include "ember.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include "memtrace.h"

class Ember;

/// <summary>
/// Két emberre mutató pointert tárol, akik között fennáll a kapcsolat, továbbá az azonosítóját és egy időpillanatot, amikor létrejött.
/// Lehet rajta keresztül a hívó személynek üzenetet küldeni a hívott részére.
/// </summary>
class Kapcsolat {
	Ember* hivo;
	Ember* cel;
	std::time_t kezdet;	/// kapcsolat létrehozásának időpontja
	int id;	///azonosítószám a könnyebb kezelésért, a hívó és a foogadó fél telefonszámainak az összefűzése (8 jegyű)

public:


	/// <summary>
	/// A telefonközpont adja neki az emberek referenciáit, beállítja a kezdőidőt.
	/// </summary>
	/// <param name="h">A hívó fél</param>
	/// <param name="c">A hívott fél</param>
	/// <param name="azon">A kapcsolat leendő azonosítója</param>
	Kapcsolat(Ember* h = NULL, Ember* c = NULL, int azon=0):hivo(h), cel(c), id(azon)
	{
		
			auto start = std::chrono::system_clock::now();

			kezdet = std::chrono::system_clock::to_time_t(start);
		
		if ((h != NULL) && (c != NULL))
		{
			hivo->setfoglalt(true);
			cel->setfoglalt(true);
		}

	}

	/// <summary>
	/// Üzenet küldés a hívott félnek,
	/// const char* kivételt dob, ha sikertelen volt.
	/// </summary>
	/// <param name="msg">Az elküldendő üzenet</param>
	void send(std::string msg) const;

	/// <summary>
	/// Id igénylés.
	/// </summary>
	/// <returns>a kapcsolat azonosítószáma</returns>
	int getid() const { return id; }
	
	/// <summary>
	/// Üzenetet küld a hívott félnek és kiírja az eltelt időt, az ember pointereket nem kell felszabadítani, majd a vektorból szabadítjuk fel őket a főprogramban.
	/// </summary>
	~Kapcsolat() {
		auto end = std::chrono::system_clock::now();
			std::time_t veg = std::chrono::system_clock::to_time_t(end);
			auto start = std::chrono::system_clock::from_time_t(kezdet);
			std::chrono::duration<double> eltelt_p = end - start;
			double elteltcnt = eltelt_p.count();

			if (elteltcnt > 1)
			{
				// ReSharper disable once CppDeprecatedEntity
				std::cout << "Hivas vege ekkor:" << std::ctime(&veg) << "Eltelt ido: " << eltelt_p.count() << " masodperc" << std::endl;  // NOLINT(clang-diagnostic-deprecated-declarations)
			}
			else
			{
				std::cout << "A kapcsolat nem jott etre." << std::endl;
			}
		
		
		if ((hivo != NULL) && (cel != NULL)) {
			hivo->setfoglalt(false);
			cel->setfoglalt(false);

			if (elteltcnt > 1) {
				try { send("A kapcsolat megszakadt. -> Tovabbi szep napot! :)"); }
				catch (const char* exc) { std::cerr << "\n^^" << exc << "^^" << std::endl; }
			}
		}
		
	}

	/// <summary>
	/// << operátor, hogy a kapcsolatokat ki lehessen írni egy os-re
	/// </summary>
	/// <param name="os">kimeneti folyam</param>
	/// <param name="k">egy kapcsolatra mutató pointer</param>
	/// <returns>kimeneti folyam</returns>
	friend std::ostream& operator<<(std::ostream& os, Kapcsolat* k) {
		return os << " +\tA hivo ugyfel: " << k->hivo << "\n\tA hivott ugyfel: " << k->cel << "\n\tA kapcsolat azonositoja: " << k->id << std::endl;
	}
};


