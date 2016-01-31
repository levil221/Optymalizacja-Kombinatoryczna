#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include "generator.hpp"
#include "populacja.hpp"
using namespace std;

void wczytaj(vector<zad> &o1, vector<konserwacja> &o2,string filename,int ii);
void wypisz(int ile, vector<zad> & o1, vector < konserwacja> & o2);

int main()
{
	srand(time(NULL));
	vector<zad> oZad;
	vector<konserwacja> oKonserwa;
	string filename,
			buf;
	int menu,
		ilosc_zadan,
		ilosc;
	cout << "1. Generuj instancje\n";
	cout << "2. Rozwiaz instancje\n";
	cin >>menu;

	switch (menu)
	{
	case 1:
	{
		cout << "podaj nazwe dla pliku:\n";
		cin >> filename;
		filename += ".txt";
		cout << "\npodaj ilosc zadan:\n";
		cin >> ilosc_zadan;
		generator gen(filename,ilosc_zadan);
		gen.generujZadania();
		gen.generujPrzerwy();
		gen.zapisz();
		cout << "\n\nwygenerowano";
	}
	break;
	case 2:
	{
		int licznoscPopulacji;
		vector<populacja> populus;
		populacja *tmp;
		cout << "podaj nazwe pliku do wczytania(bez rozserzenaia):\n";
		cin >> filename;
		cout << "podaj rozmiar populacji: ";
		cin >> licznoscPopulacji;
		populus.reserve(licznoscPopulacji);
		filename += ".txt";
		ilosc = 0;
		wczytaj(oZad, oKonserwa, filename, ilosc);
		for (int i = 0; i <= licznoscPopulacji; i++)				//inicializacja
		{
			tmp = new populacja;
			tmp->insta.nr = i;
			populus.push_back(*tmp);
			populus[i].inicializuj(oZad, oKonserwa);
		}
		for (int x = 0; x <= 300; x++)									//Ewolucja
			{
				for (int i = 0; i <= licznoscPopulacji / 2; i+=2)			//selekcja
				{
					int a = populus[i].insta.czas_m1 < populus[i].insta.czas_m2 ? populus[i].insta.czas_m2 : populus[i].insta.czas_m1;
					int b = populus[i + 1].insta.czas_m1 < populus[i + 1].insta.czas_m2 ? populus[i + 1].insta.czas_m2 : populus[i + 1].insta.czas_m1;
					if (a < b)
					{
						populus[i + 1] = populus[i ];
					}
					else
					{
						populus[i] = populus[i+1];
					}
				}
					for (int i = 0; i <= licznoscPopulacji / 2; i += 2)			//przetasowanie
				{
					populacja temp;
					int a = rand() % licznoscPopulacji;
					int b = rand() % licznoscPopulacji;
					temp = populus[a];
					populus[a] = populus[b];
					populus[b] = temp;
				}
				int iloscMutacji = rand() % (int)(licznoscPopulacji*0.2) + (int)(licznoscPopulacji*0.1);
				for (int i = 0; i <= iloscMutacji; i += 2)					//mutacja
				{
					populus[rand() % licznoscPopulacji].mutacja(oZad,oKonserwa);
				}/*
				int iloscCrossOver = licznoscPopulacji - iloscMutacji;
				for (int i = 0; i <= iloscCrossOver / 2; i += 2)			//krzyzowanie
				{
					int a = rand() % licznoscPopulacji;
					int b = rand() % licznoscPopulacji;
					populus[a].krzyzowanie(populus[b].insta);
				}*/
			
		_getch();
		system("cls");
		for (int x = 0; x <= licznoscPopulacji; x++)
			populus[x].wypisz();
		}
	}
	break;
	}

	_getch();
	return 0;
}

void wczytaj(vector<zad> &o1, vector < konserwacja> &o2, string filename,int ii)
{
	string buf;
	fstream file;
	int ile1;
	zad tempZad;
	konserwacja tempKonserwa;
	file.open(filename.c_str(), ios::in);
	if (!file.is_open())
		cout << "\nblad otwarcia pliku";
	else
	{
		getline(file, buf);
		ile1 = atoi(buf.c_str());
		ii = ile1;
		for (int i = 0; i <= ile1; i++)
		{
			getline(file, buf, ';');
			tempZad.czas_op1 = atoi(buf.c_str());
			getline(file, buf, ';');
			tempZad.czas_op2 = atoi(buf.c_str());
			getline(file, buf, ';');
			tempZad.maszyna_op1 = atoi(buf.c_str());
			getline(file, buf);
			tempZad.maszyna_op2 = atoi(buf.c_str());
			tempZad.czas_konca = 0;
			o1.push_back(tempZad);
		}

		getline(file, buf);
		ile1 = atoi(buf.c_str());

		for (int i = 0; i <= ile1; i++)
		{
			getline(file, buf, ';');
			getline(file, buf, ';');
			tempKonserwa.time = atoi(buf.c_str());
			getline(file, buf, ';');
			tempKonserwa.begin = atoi(buf.c_str());
			getline(file, buf);
			tempKonserwa.end = atoi(buf.c_str());
			o2.push_back(tempKonserwa);
		}

	}
}

void wypisz(int ile, vector<zad> &o1, vector < konserwacja> &o2)
{
	for (int i = 0; i <= o1.size(); i++)
	{
		cout << o1[i].czas_op1 << " " << o1[i].czas_op2 << "\n";
	}
	cout << endl;
	for (int i = 0; i <= ile; i++)
	{
		cout << o2[i].time << " ";
		{

		}
	}

}