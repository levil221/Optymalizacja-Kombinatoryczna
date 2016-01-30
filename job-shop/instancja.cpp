#include "instancja.hpp"

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
	this->ile = oZad.size();
	///////////////////////////////////////init tablicy z rozwiazaniem i czasami
	for (int i = 0; i <= 2; i++)
		this->rozwiazanie[i] = new task[oZad.size()];
	for (int i = 0; i <= 2; i++)
		this->czas[i] = new czasOperacji[oZad.size()];
	//////////////////////////////////////
	cout << "********************\n";
	////////////////////////////////////
	for (int i = 0; i < oZad.size(); i++)
	{
		zad1 = rand() % oZad.size();
		zad2 = rand() % oZad.size();
		while (zad1 == zad2)
			zad1 = rand() % oZad.size();
		dd++;
		zapetlenie = 0;
		while (dodano < dd)
		{
			if (oZad[zad1].maszyna_op1 == 1 && oZad[zad1].op1 == false)//op1 na m1
			{
			this->rozwiazanie[1][i].zdanie = zad1;
			this->rozwiazanie[1][i].operacja = 1;
				oZad[zad1].op1 = true;
				dd = ++dodano;
				mm = 1;
				this->czas[1][i].begin =i-1<0 ? 0:this->czas[1][i - 1].end;
				currenttime_m1+=this->czas[1][i].time = oZad[zad1].czas_op1;
				oZad[zad1].czas_konca = this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
				break;
			}
			else if (oZad[zad1].maszyna_op1 == 2 && oZad[zad1].op1 == false)//op1 na m2
			{
				this->rozwiazanie[2][i].zdanie = zad1;
				this->rozwiazanie[2][i].operacja = 1;
				oZad[zad1].op1 = true;
				dd = ++dodano;
				mm = 2;
				this->czas[2][i].begin = i - 1<0 ? 0 : this->czas[2][i - 1].end;
				currenttime_m2 += this->czas[2][i].time = oZad[zad1].czas_op1;
				oZad[zad1].czas_konca = this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
				break;
			}
			else if (oZad[zad1].maszyna_op2 == 1 && oZad[zad1].op1 == true && oZad[zad1].op2 == false && oZad[zad1].czas_konca < currenttime_m1)//op2 na m1
			{
				this->rozwiazanie[1][i].zdanie = zad1;
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
				this->rozwiazanie[2][i].zdanie = zad1;
				this->rozwiazanie[2][i].operacja = 2;
				oZad[zad1].op2 = true;
				dd = ++dodano;
				mm = 2;
				this->czas[2][i].begin = this->czas[2][i - 1].end;
				currenttime_m2 += this->czas[2][i].time = oZad[zad1].czas_op2;
				this->czas[2][i].end = this->czas[2][i].time + this->czas[2][i].begin;
				break;
			}
			zad1 = rand() % oZad.size();
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
					this->rozwiazanie[2][i].zdanie = zad2;
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
					this->rozwiazanie[2][i].zdanie = zad2;
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
					this->rozwiazanie[1][i].zdanie = zad2;
					this->rozwiazanie[1][i].operacja = 1;
					oZad[zad2].op1 = true;
					dd = ++dodano;
					
						this->czas[1][i].begin = i - 1<0 ? 0 : this->czas[1][i - 1].end;
						currenttime_m1 += this->czas[1][i].time = oZad[zad2].czas_op1;
						oZad[zad2].czas_konca = this->czas[1][i].end = this->czas[1][i].time + this->czas[1][i].begin;
					
					break;
				}
				else	if (oZad[zad2].maszyna_op2 == 1 && oZad[zad2].op1 == true && oZad[zad2].op2 == false && oZad[zad2].czas_konca < currenttime_m1)
				{
					this->rozwiazanie[1][i].zdanie = zad2;
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
				this->rozwiazanie[oZad[zad2].maszyna_op2][i].zdanie = zad2;
				this->rozwiazanie[oZad[zad2].maszyna_op2][i].operacja = 2;
				oZad[zad2].op2 = true;
				dd = ++dodano;
				//sprawdzamy czy czas maszyny przeciwnej jest wiekszy niz na tej ktorej chcemy dodac
				this->czas[oZad[zad2].maszyna_op2][i].begin = oZad[zad2].czas_konca > czas[oZad[zad2].maszyna_op2][i-1].end ? oZad[zad2].czas_konca : czas[oZad[zad2].maszyna_op2][i - 1].end;
				currenttime_m1 += this->czas[1][i].time = oZad[zad1].czas_op2;
				this->czas[oZad[zad2].maszyna_op2][i].end = this->czas[oZad[zad2].maszyna_op2][i].time + this->czas[oZad[zad2].maszyna_op2][i].begin;
				break;
			}
			zad2 = rand() % oZad.size();
			zapetlenie++;
		}
	//	cout << this->rozwiazanie[1][i].zdanie<<"op"<< this->rozwiazanie[1][i].operacja <<"->" <<this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zdanie << "op" << this->rozwiazanie[2][i].operacja << "->"<< this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
	}
	///////////////////////////////////////////
	for (int i = 0; i < oZad.size(); i++)
	{
		oZad[i].op1 = false;
		oZad[i].op2 = false;
		oZad[i].czas_konca = 0;
	}
}


void instancja::wyliczCzas(vector<konserwacja> oKonserwa, vector<zad> &oZad)
{//////////////////////////////////////////////////////////////////////////////////////
	int licznik_przerw = 0,
		nrzadania,
		temp=0,
		temptime,
		iddletime,
		finetime;
	czas_m1 = this->czas[1][ile-1].end;
	czas_m2 = 0;
///////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < ile; i++)
	{
		if (oKonserwa[licznik_przerw].begin < czas_m2 + this->czas[2][i].time &&licznik_przerw < oKonserwa.size()-1)			//czy nachodzi na przerwe
		{
			iddletime = oKonserwa[licznik_przerw].begin - this->czas[2][i - 1].end;											//czas bezczynnosci - czas do przerwy konserwacyjnej
			finetime = czas_m2 + this->czas[2][i].time + oKonserwa[licznik_przerw].time + (this->czas[2][i].time*0.3) + 1;	//czas kary jesli przeczekamy przerwe konserwacyjna
			temptime = iddletime + this->czas[2][i].time + czas_m2 + oKonserwa[licznik_przerw].time;						//czas rozpoczecia zadania z przerwa
			licznik_przerw++;
			if (temptime < finetime)
				temp = temptime;
			else temp = finetime;
			while (this->czas[2][i].begin + this->czas[2][i].time +temp > oKonserwa[licznik_przerw].begin && licznik_przerw < oKonserwa.size()-1)	//jesli nachodzi na wiecej niz jedna przerwe
			{
				iddletime += oKonserwa[licznik_przerw].begin - oKonserwa[licznik_przerw - 1].end;						//roznia czasow miedzy poczatkiem nastepnej a koncem poprzedniej rpzerwy
				finetime += ((double)czas[2][i].time*0.3) + 1 + oKonserwa[licznik_przerw].time;
				temptime += iddletime + oKonserwa[licznik_przerw].time;
				licznik_przerw++;	
				if (temptime < finetime)
					temp = temptime;
				else temp = finetime;
			}
			if (temptime < finetime)				//kara czy przerwa ? oto jest pytanie
			{
				this->czas[2][i].begin = oKonserwa[licznik_przerw-1].end;
				this->czas[2][i].end = this->czas[2][i].begin + this->czas[2][i].time;
				czas_m2 = this->czas[2][i].end;
				if(rozwiazanie[2][i].operacja==1)											//jezeli byla to operacja 1 to zmieniamy czas dla poczatku operacji 1
					oZad[rozwiazanie[2][i].zdanie].czas_konca =this->czas_m2;
				this->update(i, oZad);
			}
			else
			{
				czas_m2 = this->czas[2][i].end = finetime;
			if (rozwiazanie[2][i].operacja == 1)								//jezeli byla to operacja 1 to zmieniamy czas dla poczatku operacji 1
				oZad[rozwiazanie[2][i].zdanie].czas_konca = this->czas_m2;
			this->update(i, oZad);
			}
		}
		
		else//nie nachodzi na konserwacje
		{
			czas_m2 = this->czas[2][i].end;
			if (rozwiazanie[2][i].operacja == 1)
				oZad[rozwiazanie[2][i].zdanie].czas_konca = this->czas_m2;
			this->update(i, oZad);
		}
		//oZad[rozwiazanie[2][i].zdanie].czas_konca = czas_m2;
//////////////////////////////////////////////////////////////////////////////////////////////////////////		
		cout << this->rozwiazanie[1][i].zdanie << "op" << this->rozwiazanie[1][i].operacja << "->" << this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zdanie << "op" << this->rozwiazanie[2][i].operacja << "->" << this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
		
	}
}

void instancja::wyswietl()
{
	cout << "\ninit nr " << nr << "\nM1: ";
	for (int i = 0; i <ile; i++)
	{
		cout << this->rozwiazanie[1][i].zdanie << "op"<< this->rozwiazanie[1][i].operacja<<" ";

	}

	cout << "\tczas: " << czas_m1;
	cout << "\nM2: ";
	for (int i = 0; i <ile; i++)
	{
		cout << this->rozwiazanie[2][i].zdanie << "op"<< this->rozwiazanie[2][i].operacja<<" ";

	}
	cout << "\tczas: " << czas_m2 << endl;
	//.for (int i = 0; i <ile; i++)
//	cout << this->rozwiazanie[1][i].zdanie << "op" << this->rozwiazanie[1][i].operacja << "->" << this->czas[1][i].begin << " " << this->czas[1][i].time << " " << this->czas[1][i].end << "|" << this->rozwiazanie[2][i].zdanie << "op" << this->rozwiazanie[2][i].operacja << "->" << this->czas[2][i].begin << " " << this->czas[2][i].time << " " << this->czas[2][i].end << "\n";
}

void instancja::update(int start, vector<zad> &oZad)																				// weryfikacja i update
{
	int findtask = -1;
	bool findtaskif;

	for (int i = start + 1; i < ile; i++)
	{
		this->czas[2][i].begin = czas[2][i - 1].end;
		this->czas[2][i].end = czas[2][i].begin + czas[2][i].time;
	}
		
	for (int i = 0; i < start; i++)
		if (rozwiazanie[1][start].zdanie == rozwiazanie[2][i].zdanie)
			findtask = i;
	findtaskif = findtask < 0 ? false : true;
	if (!findtaskif)
		findtask = 0;
	if (czas[1][start].begin < oZad[findtask].czas_konca && rozwiazanie[1][start].operacja == 2 && findtaskif)
	{
		this->czas[1][start].begin = oZad[findtask].czas_konca;
		this->czas[1][start].end = czas[1][start].begin + czas[1][start].time;
		for (int j = start + 1; j <= ile; j++)
		{
			this->czas[1][j].begin = czas[1][j - 1].end;
			this->czas[1][j].end = czas[1][j].begin + czas[1][j].time;
		}
	}
}

instancja::instancja()
{
	rozwiazanie = new task *[2];
	czas = new czasOperacji *[2];
}
