#include "generator.hpp"



void generator::generujPrzerwy()
{
	
	int podzial;
	ilosc_przerw = rand()%(ilosc_zadan/2) +1;
	konserwacja temp;
	
	this->getTime();
	podzial = czas_m2 / ilosc_przerw;
	temp.end = 0;
	for (int i = 0; i <= ilosc_przerw; i++)
	{
		
		temp.begin = temp.end + rand()%100+1;
		temp.time = rand() % 20 + 1;
		temp.end = temp.begin + temp.time;
		przerwy.push_back(temp);
	}
}

void generator::generujZadania()
{
	
	zad temp;
	for (int i = 0; i <= ilosc_zadan; i++)
	{
		temp.czas_op1 = rand()%100+1;
		temp.czas_op2 = rand() % 100 + 1;
		temp.maszyna_op1 = rand() % 2 + 1;
		if (temp.maszyna_op1 == 1)
			temp.maszyna_op2 = 2;
		else
		{
			temp.maszyna_op2 = 1;
			temp.maszyna_op1 = 2;
		}
		this->zadanie.push_back(temp);
	}
}

void generator::getTime()
{
	for (int i = 0; i <= ilosc_zadan; i++)
	{
		if (zadanie[i].maszyna_op1 == 1)
		{
			czas_m1 += zadanie[i].czas_op1;
			czas_m2 += zadanie[i].czas_op2;
		}
		else
		{
			czas_m1 += zadanie[i].czas_op2;
			czas_m2 += zadanie[i].czas_op1;
		}
	}
}



void generator::zapisz()
{
	
	file.open(filename.c_str(), ios::out);
	if (!file.is_open())
		cout << "error otwarcia pliku";
	else
	{
		file << zadanie.size()-1<<"\n";
		for (int i = 0; i <= ilosc_zadan; i++)
		{
			file << zadanie[i].czas_op1 << ";" << zadanie[i].czas_op2 << ";" << zadanie[i].maszyna_op1 << ";" << zadanie[i].maszyna_op2 << "\n";
		}
	}
	file << przerwy.size() << "\n";
	for (int i = 0; i <= ilosc_przerw; i++)
	{
		file << i << ";" << przerwy[i].time << ";" << przerwy[i].begin << ";" << przerwy[i].end << "\n";
	}
	file.close();
}

generator::generator()
{
}

generator::generator(string name, int ile)
{
	filename = name;
	ilosc_zadan = ile;
	czas_m1 = 0;
	czas_m2 = 0;
}


