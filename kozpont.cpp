/// @file kozpont.cpp: tartalmazza a Kozpont osztály függvényeinek a megvalósítását

#include "kozpont.h"


//#define TESZT

/// <summary>
/// Gondoskodik a kapcsolat befejezésének az eldöntéséről
/// </summary>
/// <param name="id">a kapcsolat azonosítója</param>
/// <param name="ck">a hívott fél körzete</param>
/// <param name="kozpontok">a központokat tároló vektorra mutató pointer</param>
void Kozpont::befejeze(int id, int ck, vector<Kozpont*>* kozpontok)  {
	
	cout << "Ha be szeretne fejezni a kapcsolatot, nyomjon egy 'x'-et, kulonben pedig egy masik karektert es egy ENTER-t! (szokozt, tabulatort ne alkalmazzon!)\n" << endl;
	string ans = "mas";
	cin >> ans;
	if (ans == "x" || cin.eof())
	{
		try 
		{
			end(id);
			if (ck != korzet) {
				for (size_t i = 0; i < kozpontok->size();i++) {
					if (kozpontok->at(i)->getkorzet() == ck) {
						try {
							kozpontok->at(i)->end(id);
							break;
						}
						catch (const char* exc) {
							cerr << "\n^^" << exc <<"^^"<< endl;
							break;
						}
					}
				}
			}
		}
		catch(const char* exc){
			cerr << "\n^^" << exc << "^^" << endl;
			return;
		}
	}
	return;
}

/// <summary>
/// Híváskezdeményezés,
/// const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="hivo">A hívó telefonszáma</param>
/// <param name="cel">A hívott telefonszáma</param>
/// <param name="kozpontok">A központok tárolójának a pointere</param>
/// <param name="emberek">Az emberek tárolójának a pointere</param>
void Kozpont::call(int hivo, int cel, vector<Kozpont*>* kozpontok, vector<Ember*>* emberek)
{
	int id = hivo * 10000 + cel;
	int hk = hivo / 1000;
	int ck = cel / 1000;



	if (ktabla.contains(id)) {
		Kapcsolat* aktual = ktabla.idtokapcs(id);
		if (hk == korzet && aktual != NULL) {
			cout << "\n	Kapcsolodas egy mar korabban elinditott hivashoz ...\n" << endl;
			
			uzenetkuldes(aktual);
			befejeze(id, ck, kozpontok);
			
		}
		return;
	}
	else
	{
		size_t h = -1;
		size_t c = -1;
		size_t emsz = emberek->size();

		size_t i;
		for (i = 0; i < emsz;i++) {
			if ((int) emberek->at(i)->gettel() == hivo) {
				h = i;
				if (emberek->at(h)->foglalte()) {

					throw "A hivo fel mar benne van egy kapcsolatban, nem lehet tobbet kezdemenyezni!";
				}
			}
			else if ((int) emberek->at(i)->gettel() == cel)
			{
				c = i;
				if (emberek->at(c)->foglalte())
				{
					throw "Foglalt a hivott fel, probalja ujra kesobb!";
				}
			}
			if (h < emsz && c < emsz)
			{
				break;
			}

		}
		if (h >= emsz || c >= emsz)
		{
			throw "Nem talaltunk ilyen telefonszamu embereket :(";
		}

		Kapcsolat* uj = new Kapcsolat(emberek->at(h), emberek->at(c), id);
		emberek->at(h)->setfoglalt(true);
		emberek->at(c)->setfoglalt(true);


		if (hk == ck)	// belső kapcsolat lesz
		{
			try {
				ktabla.add(uj, true);
				
				uzenetkuldes(uj);
				befejeze(id, ck, kozpontok);

				return;
			}
			catch (const char*)
			{
				throw;
			}
		}
		else if (hk == korzet)	// külső kapcsolat lesz, ez a kezdemenyezo kozpont
		{
			for (size_t pos = 0; pos < kozpontok->size(); pos++)
			{
				if (kozpontok->at(pos)->getkorzet() == ck)	// megkeresi a fogado kozpontot
				{
					try {
						kozpontok->at(pos)->connect(emberek->at(h), emberek->at(c), id);

						try {
							ktabla.add(uj, false);

							uzenetkuldes(uj);
							befejeze(id, ck, kozpontok);

							return;
						}
						catch (const char*)
						{
							try {
								kozpontok->at(pos)->end(id);
							}
							catch (const char* exc1) {
								cerr << "\n^^" << exc1 << "^^" << endl;
							}
							throw;
						}
					}
					catch (const char*)
					{
						throw;
					}
				}
			}
			throw "Nem talaltuk a hivott fel korzetet. :(";
		}

		else {
			throw "A hivo telefonszama nem tartozik a kozponthoz.";
		}
	}
}

/// <summary>
/// Vele lehet megtekinteni az éppen fennálló kapcsolatait a központnak és létrehozni új kapcsolatot
/// </summary>
void Kozpont::kapcsolatok() const
{
	ktabla.check();
}

/// <summary>
/// Egy kapcsolat megszűntetése és törlése a kapcsolótáblából, a kapcsolatot es a pointerét mindig a hívó ügyfél központja törölje.
/// Const char* kivételt dob, ha sikertelen volt.
/// </summary>
/// <param name="azon">A kapcsolat azonosítószáma</param>
void Kozpont::end(int azon)
{
	try {
		ktabla.remove(azon);
		return;
	}
	catch (const char*)
	{
		throw;
	}
}

/// <summary>
/// Gondoskodik a kapcsolaton belüli üzenetküldés vezérléséről
/// </summary>
/// <param name="uj">A kapcsolatra mutató pointer</param>
void Kozpont::uzenetkuldes(Kapcsolat* uj) const {
	cout << "\nA kapcsolat sikeresen letrejott, ha szeretne kuldeni egy uzenetet a hivott felnek, irja be ENTER-ek nelkul!\n(csak a legvegen hasznalja a kuldeshez!, az uzenetet nagybetuvel kezdje!)"
		"\nHa nem szeretne uzenetet kuldeni, akkor 'y'-t nyomjon, majd ENTER-t!\n" << endl;
#ifndef TESZT
	string msg;
	cin.ignore();
	cp::getline(cin, msg);
#endif // !TESZT
#ifdef TESZT
	string msg = "Szia! Ez egy tesztuzenet. Ne valaszolj ra.";
#endif // TESZT

	if (msg == "y")
		return;
	else
	{

			if (uj != NULL) {
				try {
					uj->send(msg);
				}
				catch (const char* exc) {
					cerr<<"\n^^"<< exc<<"^^"<<endl;
					return;
				}
			}
		
		else
		{
			throw "Nem talaltuk a kapcsolatot, ennek nem kene elofordulnia :(. Szoljon a fejlesztonek, hogy szegyelje ossze magat!";
		}

	}
}

/// <summary>
/// Kapcsol egy távolsági hívást,
/// const char* kivételt dob, ha sikertelen volt
/// </summary>
/// <param name="hivo">a hívó emberre mutató pointer</param>
/// <param name="cel">a hívott emberre mutató pointer</param>
/// <param name="id">a kapcsolat leendő azonosítója</param>
void Kozpont::connect(Ember* hivo, Ember* cel, int id) {
	Kapcsolat* uj = new Kapcsolat(hivo, cel, id);

	try {
		ktabla.add(uj, false);
		return;
	}
	catch (const char*) {
		throw;
	}
}
