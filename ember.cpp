/// @file ember.cpp: tartalmazza az Ember osztály függvényeinek a definícióit

#include "ember.h"


/// <summary>
/// Konstruktor
/// </summary>
/// <param name="n">név</param>
/// <param name="tel">telefonszám - négyjegyű</param>
/// <param name="max">üzenettárhely mérete, alapértelmezetten 10</param>
Ember::Ember(std::string n , int tel , unsigned int max = 10) : nev(n), maxmsg(max), telszam(tel), olvasatlan(0), foglalt(false)
{
	tarhely = new std::string[max];
	for (size_t i = 0; i < max; i++)
			tarhely[i] = "";
	
}

/// <summary>
/// Üzenet fogadása a fennálló kapcsolaton keresztül.
/// Const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="msg">A fogadott üzenet</param>
void Ember::recieve(std::string msg) {
	for (size_t i = 0; i < maxmsg; i++)
	{
		if (tarhely[i] == "")
		{
			olvasatlan++;
			tarhely[i] = msg;
			return;
		}
	}
	throw  "Betelt a hivott fel tarhelye.";
}

/// <summary>
/// Az üzenetek kezelése / olvasása, törlése.
/// </summary>
void Ember::uzenetek() {

	std::cout << "\n\nOnnek " << olvasatlan << " olvasatlan uzenete van.\n	Az uzenetei:\n\n" << std::endl;
	olvasatlan = 0;

	for (size_t i = 0; i < maxmsg; i++)
	{
		if (tarhely[i] != "")
		{

			std::cout <<"\n  -  "<< tarhely[i] << "\n\nNyomja meg az egyik billentyut!:\n	Kovetkezo uzenet - 'k' ...vagy... Torles - 't'\n";
			char c;
			std::cin >> c;
			if (std::cin.eof())
				throw "Ctrl Z";
			switch (c) {
			case 't':
				tarhely[i] = "";
				std::cout << " -torles-\n" << std::endl;
				break;
			case 'k':
				break;
			default:
				std::cout << "	----rossz gombot nyomott meg, nem torlunk----\n";
				break;
			}

		}
	}
	std::cout << "	Nincs tobb uzenete.\n	Az osszes uzenet torlesehez nyomjon egy 'd' billentyut, vagy barmelyik masik karaktert, ha nem szeretne torolni oket!" << std::endl;
	char c;
	std::cin >> c;
	if (std::cin.eof())
		throw "Ctrl Z";
	if (c == 'd')
	{
		for (size_t i = 0; i < maxmsg; i++)
		{
			tarhely[i] = "";
			std::cout << "-";
		}
	}

	std::cout << "\n	O_O Nincs tobb olvasando uzenete, szep napot! O_O\n\n" << std::endl;
}