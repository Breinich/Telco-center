/// @file kapcsolat.cpp: tartalmazza a Kapcsolat osztály függvényeinek a megvalósítását

#include "kapcsolat.h"

/// <summary>
/// Üzenet küldés a hívott félnek,
/// const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="msg">Az elküldendő üzenet</param>
void Kapcsolat::send(std::string msg) const
{
	
		try{
			cel->recieve(msg);
			std::cout << "\n----az uzenet elkuldve----\n" << std::endl;
			return;
		}
		catch (const char*) {
			std::cout<< "__Nem sikerult elkuldeni az uzenetet.__"<<std::endl;
			throw;
		}
		
	
}
