#include "instancja.hpp"
#include <assert.h>
#include <conio.h>

void instancja::inicjalizuj(vector<zad> oZad)
{
	
	int zad1=0,
		zad2=0,
		dd = 0,
		dodano = 0,
		mm,
		currenttime_m1=0,
		currenttime_m2=0,
		zapetlenie=0;
	iddleTime *tempiddletime;

	this->ile = oZad.size()-1;
	///////////////////////////////////////init tablicy z rozwiazaniem i czasami
	for (int i = 0; i <= 2; i++)
		this->rozwiazanie[i] = new task[oZad.size()];
	for (int i = 0; i <= 2; i++)
		this->czas[i] = new czasOperacji[oZad.size()];
	//////////////////////////////////////
	//cout << "********************\n";
	////////////////////////////////////
	for (int i = 0; i < oZad.size()-1 ; i++)
	{
		zad1 = rand() % (oZad.size() - 1) + 1;
		zad2 = rand() % (oZad.size() - 1) + 1;
		while (zad1 == zad2)
			zad1 = rand() % (oZad.size() - 1) + 1;
		dd++;
		zapetlenie = 0;
		while (dodano < dd)
		{
			if (oZad[zad1].maszyna_op1 == 1 && oZad[zad1].op1 == false)//op1 na m1
			{
			this->rozwiazanie[1][i].zadanie = zad1;
			this->rozwiazanie[1][i].operacja = 1;
				oZad[zad1].op1 = true;
				dd = ++dodano;
				mm = 1;
				this->czas[1][i].begin =i-1 < 0 ? 0:this->czas[1][i - 1].end;
				currenttime_m1+=this->czas[1][i].time = oZad[zad1].czas_op1;
				oZad[zad1].czas_konca = this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
				break;
			}
			else if (oZad[zad1].maszyna_op1 == 2 && oZad[zad1].op1 == false)//op1 na m2
			{
				this->rozwiazanie[2][i].zadanie = zad1;
				this->rozwiazanie[2][i].operacja = 1;
				oZad[zad1].op1 = true;
				dd = ++dodano;
				mm = 2;
				this->czas[2][i].begin = i - 1 < 0 ? 0 : this->czas[2][i - 1].end;
				currenttime_m2 += this->czas[2][i].time = oZad[zad1].czas_op1;
				oZad[zad1].czas_konca = this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
				break;
			}
			else if (oZad[zad1].maszyna_op2 == 1 && oZad[zad1].op1 == true && oZad[zad1].op2 == false && oZad[zad1].czas_konca < currenttime_m1)//op2 na m1
			{
				this->rozwiazanie[1][i].zadanie = zad1;
				this->rozwiazanie[1][i].operacja = 2;
				oZad[zad1].op2 = true;
				dd = ++dodano;
				mm = 1;
				this->czas[1][i].begin =  this->czas[1][i - 1].end;
				currenttime_m1 += this->czas[1][i].time = oZad[zad1].czas_op2;
				this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
				break;
			}
			else if (oZad[zad1].maszyna_op2 == 2 && oZad[zad1].op1 == true && oZad[zad1].op2 == false && oZad[zad1].czas_konca < currenttime_m2)//op2 na m2
			{
				this->rozwiazanie[2][i].zadanie = zad1;
				this->rozwiazanie[2][i].operacja = 2;
				oZad[zad1].op2 = true;
				dd = ++dodano;
				mm = 2;
				this->czas[2][i].begin = this->czas[2][i - 1].end;
				currenttime_m2 += this->czas[2][i].time = oZad[zad1].czas_op2;
				this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
				break;
			}
			zad1 = rand() % (oZad.size()-1) + 1;
			zapetlenie++;
		}
			++dd;
			zapetlenie = 0;
		while (dodano < dd)
		{
			if (mm == 1)
			{				
				if (oZad[zad2].maszyna_op1 == 2 && oZad[zad2].op1 == false)//op1 na m2
				{
					this->rozwiazanie[2][i].zadanie = zad2;
					this->rozwiazanie[2][i].operacja = 1;
					oZad[zad2].op1 = true;
					dd = ++dodano;
					
						this->czas[2][i].begin = i - 1<0 ? 0 : this->czas[2][i - 1].end;
						currenttime_m2 += this->czas[2][i].time = oZad[zad2].czas_op1;
						oZad[zad2].czas_konca = this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
					
					break;
				}
				else if (oZad[zad2].maszyna_op2 == 2 && oZad[zad2].op1 == true && oZad[zad2].op2 == false && oZad[zad2].czas_konca < currenttime_m2)//op2 na m2
				{
					this->rozwiazanie[2][i].zadanie = zad2;
					this->rozwiazanie[2][i].operacja = 2;
					oZad[zad2].op2 = true;
					dd = ++dodano;
					if (zad1 == zad2)//zrobienie przerwy by wykonala sie op1
					{
						this->czas[2][i].begin = this->czas[2][i - 1].end + oZad[zad1].czas_op1;
						currenttime_m2 += this->czas[2][i].time = oZad[zad2].czas_op2;
						this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
					}
					else
					{
						this->czas[2][i].begin =  this->czas[2][i - 1].end;
						currenttime_m2 += this->czas[2][i].time = oZad[zad2].czas_op2;
						this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
						break;
					}
				}
			}
			else if (mm == 2)
			{
				if (oZad[zad2].maszyna_op1 == 1 && oZad[zad2].op1 == false)
				{
					this->rozwiazanie[1][i].zadanie = zad2;
					this->rozwiazanie[1][i].operacja = 1;
					oZad[zad2].op1 = true;
					dd = ++dodano;
					
						this->czas[1][i].begin = i - 1 < 0 ? 0 : this->czas[1][i - 1].end;
						currenttime_m1 += this->czas[1][i].time = oZad[zad2].czas_op1;
						oZad[zad2].czas_konca = this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
					
					break;
				}
				else	if (oZad[zad2].maszyna_op2 == 1 && oZad[zad2].op1 == true && oZad[zad2].op2 == false && oZad[zad2].czas_konca < currenttime_m1)
				{
					this->rozwiazanie[1][i].zadanie = zad2;
					this->rozwiazanie[1][i].operacja = 2;
					oZad[zad2].op2 = true;
					dd = ++dodano;
					if (zad1 == zad2)//zrobienie przerwy by wykonala sie op1
					{
						this->czas[1][i].begin = this->czas[1][i - 1].end + oZad[zad1].czas_op1;
						currenttime_m1 += this->czas[1][i].time = oZad[zad2].czas_op2;
						this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
					}
					else
					{
						this->czas[1][i].begin = this->czas[1][i - 1].end;
						currenttime_m1 += this->czas[1][i].time = oZad[zad2].czas_op2;
						this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
					}
					break;
				
				}
			}
			if ((oZad[zad2].czas_konca > currenttime_m1 && zapetlenie > 1000) || (oZad[zad2].czas_konca > currenttime_m2 && zapetlenie > 1000))//na zapetlajace sie !@#
			{
				// nr maszyny pobieramy z zadabia ktore sie zapetla
				this->rozwiazanie[oZad[zad2].maszyna_op2][i].zadanie = zad2;
				this->rozwiazanie[oZad[zad2].maszyna_op2][i].operacja = 2;
				oZad[zad2].op2 = true;
				dd = ++dodano;
				//sprawdzamy czy czas maszyny przeciwnej jest wiekszy niz na tej ktorej chcemy dodac
				this->czas[oZad[zad2].maszyna_op2][i].begin = oZad[zad2].czas_konca > czas[oZad[zad2].maszyna_op2][i-1].end ? oZad[zad2].czas_konca : czas[oZad[zad2].maszyna_op2][i - 1].end;
				this->czas[oZad[zad2].maszyna_op2][i].time = oZad[zad2].czas_op2;
				currenttime_m1 += this->czas[1][i].time = oZad[zad1].czas_op2;
				this->czas[oZad[zad2].maszyna_op2][i].end = this->czas[oZad[zad2].maszyna_op2][i].time + this->czas[oZad[zad2].maszyna_op2][i].begin;
				break;
			}
			zad2 = rand() % (oZad.size() - 1) + 1;
			zapetlenie++;
		}
		//debug only
		//cout << this->rozwiazanie[1][i].zadanie<<"op"<< this->rozwiazanie[1][i].operacja <<"->" <<this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zadanie << "op" << this->rozwiazanie[2][i].operacja << "->"<< this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
	}
	///////////////////////////////////////////
	for (int i = 0; i < oZad.size()-1; i++)
	{
		oZad[i].op1 = false;
		oZad[i].op2 = false;
		oZad[i].czas_konca = 0;
	}
}


void instancja::wyliczCzas(vector<konserwacja> oKonserwa, vector<zad> &oZad,int i,int _czasm2)
{//================================================================================================
	int licznik_przerw = 0,
		licznik_czekania = 0,
		nrzadania,
		temp=0,
		temptime,
		iddletime,
		finetime;
	czas_m1 = this->czas[1][ile-1].end;
	czas_m2 = _czasm2;
	iddleTime *tempiddletime;

	
	if (i != 0)//obliczamy gdzie jestesmy(ktora rpzeraw teraz bedzie);
	{
		while (czas[2][i - 1].end > oKonserwa[licznik_przerw].begin)
		{
			licznik_przerw++;
			if (licznik_przerw >= oKonserwa.size() - 1)
				break;
		}
		if (czas_m2 > oKonserwa[licznik_przerw].end && licznik_przerw < oKonserwa.size() - 2) licznik_przerw++;
	}
	else
	{
		for (i; i < ile; i++)
		{
			//for (int x = 0; x < ile; x++)
			//	cout << czas[2][x].begin << " " << czas[2][x].time << " " << czas[2][x].end << endl;
			if (oKonserwa[licznik_przerw].begin < czas_m2 + this->czas[2][i].time && licznik_przerw < oKonserwa.size() - 1)	//czy nachodzi na przerwe
			{

				iddletime = oKonserwa[licznik_przerw].begin - czas_m2;													//nastepna przerwa - aktualny czas maszyny
				finetime = czas_m2 + oKonserwa[licznik_przerw].time + (czas[2][i].time*1.3) + 1;		//<- aktualny czas maszyny + dlugosc przerwy + czas trwania zadania + kara 30% +1
				temptime = iddletime + czas[2][i].time + czas_m2 + oKonserwa[licznik_przerw].time;						//pozosta³y czas do przerwy technicznej + czas zadania + czas prszerwy
				if (temptime < finetime)
					temp = temptime;
				else temp = finetime;

				licznik_przerw = licznik_przerw < oKonserwa.size() - 1 ? licznik_przerw + 1 : oKonserwa.size() - 1; // upewniamy siê by licznik przerw nie przekroczyl ilosci przerw

				if (licznik_przerw < oKonserwa.size() - 1)
					while (temp > oKonserwa[licznik_przerw].begin)//<-czy nachodzimy na kolejne przerwy ?
					{
						iddletime += oKonserwa[licznik_przerw].begin - oKonserwa[licznik_przerw - 1].end;//<-doliczmy czas pomiêdzy przerwami technicznymi
						finetime += (czas[2][i].time*0.3) + 1 + oKonserwa[licznik_przerw].time;	//<-doliczamy czas kary plus dlugosc przerwy
						temptime += iddletime + oKonserwa[licznik_przerw].time;
						if (temptime < finetime)
							temp = temptime;
						else temp = finetime;
						licznik_przerw = licznik_przerw < oKonserwa.size() - 1 ? licznik_przerw + 1 : oKonserwa.size() - 1;
					}

				if (temptime < finetime)// co lepsze ?											
				{
					this->czas[2][i].begin = oKonserwa[licznik_przerw - 1].end;	//czekamy wiec zaczyna sie po ostatniej przerwie na jaka naszedl
					this->czas[2][i].end = temptime;

					tempiddletime = new iddleTime;
					tempiddletime->begin = czas_m2;
					tempiddletime->time = iddletime;
					tempiddletime->end = tempiddletime->begin + tempiddletime->time;

					iddleTime *newtemptime = new iddleTime;
					newtemptime->time = iddletime;
					czasCzekaniaM2.push_back(*newtemptime);
					//delete tempiddletime;
					this->czas_m2 = temptime;
					//cout << "CZEKA-> ";
				}
				else
				{
					this->czas[2][i].end = finetime;
					this->czas_m2 = finetime;
						//zaczyna sie w swoim starcie i konczy sie po ostatniej rpzerwie na jaka naszedl +kary
				//	cout << " KARA-> ";

				}

				if (rozwiazanie[2][i].operacja == 1)
					oZad[rozwiazanie[2][i].zadanie].czas_konca = this->czas_m2;
				this->update(i, oZad);
			}
			else
			{

				czas_m2 += this->czas[2][i].time;
				if (rozwiazanie[2][i].operacja == 1)
					oZad[rozwiazanie[2][i].zadanie].czas_konca = czas_m2;
				this->update(i-1, oZad);
			}
		}
		//oZad[rozwiazanie[2][i].zdanie].czas_konca = czas_m2;
//=================================================================================================
	//cout << this->rozwiazanie[1][i].zadanie << "op" << this->rozwiazanie[1][i].operacja << "->" << this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zadanie << "op" << this->rozwiazanie[2][i].operacja << "->" << this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
	}
	
	//cout << nr << " ";
}

void instancja::wyswietl()
{
	cout << "\ninit nr " << nr ;
	for (int i = 0; i <ile; i++)
	{
		cout << this->rozwiazanie[1][i].zadanie << "op"<< this->rozwiazanie[1][i].operacja<<" ";

	}

	cout << "\tczas: " << czas_m1;
	cout << "\nM2: ";
	for (int i = 0; i <ile; i++)
	{
		cout << this->rozwiazanie[2][i].zadanie << "op"<< this->rozwiazanie[2][i].operacja<<" ";

	}
	cout << "\tczas: " << czas_m2 << endl;
	//for (int i = 0; i <ile; i++)
	//cout << this->rozwiazanie[1][i].zadanie << "op" << this->rozwiazanie[1][i].operacja << "->" << this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zadanie << "op" << this->rozwiazanie[2][i].operacja << "->" << this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
	//cout << "************************** " << czas_m2 << endl;
}

void instancja::update(int start, vector<zad> &oZad)	// weryfikacja i update
{
	for (int i = start + 1; i < ile; i++)// zazebianie sie czasow na m2
	{
		this->czas[2][i].begin = czas[2][i - 1].end;
		this->czas[2][i].end = czas[2][i].begin + czas[2][i].time;
		if (rozwiazanie[2][i].operacja == 1)
			oZad[rozwiazanie[2][i].zadanie].czas_konca = czas[2][i].end;
	}
	//if (czas[1][start - 1].begin != 0)
	//	czas[1][start - 1].begin = 0;
	for (int i = start + 1; i < ile; i++)// zazebianie sie czasow na m1
	{
		this->czas[1][i].begin = czas[1][i - 1].end;
		this->czas[1][i].end = czas[1][i].begin + czas[1][i].time;
		if (rozwiazanie[1][i].operacja == 1)
			oZad[rozwiazanie[1][i].zadanie].czas_konca = czas[1][i].end;
	}
	
	czas_m1 = this->czas[1][ile - 1].end;
}

int instancja::findIndex(int zadanie, int maszyna)
{
	for (int i = 0; i < ile; i++)
		if (rozwiazanie[maszyna][i].zadanie == zadanie)
			return i;
}

void instancja::ustawCzas(vector<zad> &oZad)
{
	czas[1][0].begin = 0;
	czas[2][0].begin = 0;
	for (int i = 0; i < ile; i++)
	{
		//maszyna1=============
		if (rozwiazanie[1][i].operacja == 1)
		{
			czas[1][i].begin = i - 1 < 0 ? 0 : czas[1][i - 1].end;
			czas[1][i].time = oZad[rozwiazanie[1][i].zadanie].czas_op1;
			czas[1][i].end = czas[1][i].begin + czas[1][i].time;
			if (rozwiazanie[1][i].operacja == 1)
				oZad[rozwiazanie[1][i].zadanie].czas_konca = czas[1][i].end;
			
		}
		else
		{
			czas[1][i].begin = i - 1 < 0 ? 0 : czas[1][i - 1].end;
			czas[1][i].time = oZad[rozwiazanie[1][i].zadanie].czas_op2;
			czas[1][i].end = czas[1][i].begin + czas[1][i].time;
		}
		//maszyna2=============
		if (rozwiazanie[2][i].operacja == 1)
		{
			czas[2][i].begin = i - 1 < 0 ? 0 : czas[2][i - 1].end;
			czas[2][i].time = oZad[rozwiazanie[2][i].zadanie].czas_op1;
			czas[2][i].end = czas[2][i].begin + czas[1][i].time;
			if (rozwiazanie[2][i].operacja == 1)
				oZad[rozwiazanie[2][i].zadanie].czas_konca = czas[2][i].end;
		}
		else
		{
			czas[2][i].begin = i - 1 < 0 ? 0 : czas[2][i - 1].end;
			czas[2][i].time = oZad[rozwiazanie[2][i].zadanie].czas_op2;
			czas[2][i].end = czas[2][i].begin + czas[1][i].time;
		}
	}
}

void instancja::sprawdzPoprawnosc()
{
	int *tabObecnosciM1 = new int[ile];
	int *tabObecnosciM2 = new int[ile];
	int poprawnadlugosc1 = 0,poprawnadlugosc2=0;
	for (int i = 0; i < ile; i++)
	{
		tabObecnosciM1[i] = 0;
		tabObecnosciM2[i] = 0;
		if (rozwiazanie[1][i].zadanie != NULL)
			tabObecnosciM1[i] = 1;
		else {
			cout << "\nna M1 brak zadania i = " << i;
			_getch();
		}
		if (rozwiazanie[2][i].zadanie != NULL)
			tabObecnosciM2[i] = 1;
		else {
			cout << "\nna M1 brak zadania i = " << i;
			_getch();
		}
		poprawnadlugosc1 += czas[1][i].time;
		poprawnadlugosc2 += czas[2][i].time;
	}

	if (czas_m1 != czas[1][ile - 1].end)
	{
		czas_m1 = czas[1][ile - 1].end;//bledne obliczenie czasu, wiec naprawiamy
	//	cout << " czas szeregowania inny niz faktycznie M~1 ! poprawione ! " << endl;
	//	_getch();
	}
	if (czas_m2 != czas[2][ile - 1].end)
	{
		czas_m2 = czas[2][ile - 1].end;//bledne obliczenie czasu, wiec naprawiamy
	//	cout << "czas szeregowania inny niz faktycznie M~2! poprawione ! " << endl;
	//	_getch();
	}
	if (czas_m1 < poprawnadlugosc1)

	{
		cout << "Czas na M1 jest krotszy niz suma czasow trwania !!";
		_getch();
	}
	if (czas_m2 < poprawnadlugosc2)

	{
		cout << "Czas na M2 jest krotszy niz suma czasow trwania !!";
		_getch();
	}
}

void instancja::poprawczasy(vector<zad>& oZad, vector<konserwacja> oKonserwa)
{
	int *tab=new int[ile];
	for (int i = 0; i < ile; i++)
	{
		if(rozwiazanie[1][i].operacja==1)
			tab[rozwiazanie[1][i].zadanie] = czas[1][i].end;
		if (rozwiazanie[2][i].operacja == 1)
			tab[rozwiazanie[2][i].zadanie] = czas[2][i].end;
	}
	for (int i = 0; i < ile; i++)
	{
		if (czas[1][i].begin < tab[rozwiazanie[1][i].zadanie] && rozwiazanie[1][i].operacja == 2)
			{
				czas[1][i].begin = tab[rozwiazanie[1][i].zadanie];
				czas[1][i].end = czas[1][i].begin + czas[1][i].time;
				iddleTime *newtemptime = new iddleTime;
				newtemptime->time = czas[1][i].begin - czas[1][i - 1].end;
				czasCzekaniaM1.push_back(*newtemptime);
				for (int j = i + 1; j < ile; j++)// zazebianie sie czasow na m1
				{
					this->czas[1][j].begin = czas[1][j - 1].end;
					this->czas[1][j].end = czas[1][j].begin + czas[1][j].time;
					if (rozwiazanie[1][j].operacja == 1)
						oZad[rozwiazanie[1][j].zadanie].czas_konca = czas[1][j].end;
				}

				
				wyliczCzas(oKonserwa, oZad,i,czas[2][i].begin);
				for (int j = 0; j < ile; j++)
				{
					if (rozwiazanie[1][j].operacja == 1)
						tab[rozwiazanie[1][j].zadanie] = czas[1][j].end;
					if (rozwiazanie[2][j].operacja == 1)
						tab[rozwiazanie[2][j].zadanie] = czas[2][j].end;
				}
			}
		if (czas[2][i].begin < tab[rozwiazanie[2][i].zadanie] && rozwiazanie[2][i].operacja == 2)
		{
			czas[2][i].begin = tab[rozwiazanie[2][i].zadanie];
			czas[2][i].end = czas[2][i].begin + czas[2][i].time;
			iddleTime *newtemptime = new iddleTime;
			newtemptime->time = czas[2][i].begin - czas[2][i - 1].end;
			czasCzekaniaM2.push_back(*newtemptime);
			for (int j = i + 1; j < ile; j++)// zazebianie sie czasow na m1
			{
				this->czas[2][j].begin = czas[2][j - 1].end;
				this->czas[2][j].end = czas[2][j].begin + czas[2][j].time;
				if (rozwiazanie[2][j].operacja == 1)
					oZad[rozwiazanie[2][j].zadanie].czas_konca = czas[2][j].end;
			}
			wyliczCzas(oKonserwa, oZad, i, czas[2][i].begin);
			for (int j = 0; j < ile; j++)
			{
				if (rozwiazanie[1][j].operacja == 1)
					tab[rozwiazanie[1][j].zadanie] = czas[1][j].end;
				if (rozwiazanie[2][j].operacja == 1)
					tab[rozwiazanie[2][j].zadanie] = czas[2][j].end;
			}
		}
	}
	czas_m1 = this->czas[1][ile - 1].end;
	czas_m2 = this->czas[2][ile - 1].end;
}

instancja::instancja()
{
	rozwiazanie = new task *[3];
	czas = new czasOperacji *[3];
}

instancja::~instancja()
{
	
	//delete[] rozwiazanie;
	//delete[] czas;
}
