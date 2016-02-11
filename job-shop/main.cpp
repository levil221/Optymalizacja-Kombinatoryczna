#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include "generator.hpp"
#include "populacja.hpp"
#include <assert.h>
using namespace std;

void wczytaj(vector<zad> &o1, vector<konserwacja> &o2,string filename,int ii);
void wypisz(int ile, vector<zad> & o1, vector < konserwacja> & o2);
void zapisz(populacja populus, string filename, vector<konserwacja> oKonserwa,int licznosc,int startowa);
void najlepszeUszeregowanie(vector<populacja> pointer, populacja &najlepsze,int liczebnosc, int &startowa);

int main()
{
	srand(time(NULL));
	vector<zad> oZad;
	vector<konserwacja> oKonserwa;
	string filename,
			buf;
	int menu,
		ilosc_zadan,
		ilosc,
		czasPoczatkowyUszeregowania;
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
		//======================================================		Szeregowanie zadan
		int licznoscPopulacji, poczatkowaWartoscUporzadkowania = 0;;
		vector<populacja> populus;
		populacja *tmp, najlepszeRozwiazanie;
		najlepszeRozwiazanie.insta.czas_m1 = 999999;
		najlepszeRozwiazanie.insta.czas_m2 = 999999;

		cout << "podaj nazwe pliku do wczytania(bez rozserzenaia):\n";
		cin >> filename;
		cout << "podaj rozmiar populacji: ";
		cin >> licznoscPopulacji;
		
		populus.reserve(licznoscPopulacji);
		ilosc = 0;
		wczytaj(oZad, oKonserwa, filename, ilosc);
		//================================================		inicializacja
		for (int i = 0; i <licznoscPopulacji; i++)				
		{
			tmp = new populacja;
			tmp->insta.nr = i;
			populus.push_back(*tmp);
			populus[i].inicializuj(oZad, oKonserwa);
			populus[i].insta.sprawdzPoprawnosc();
		}
		//===============================================		Ewolucja
		for (int x =0; x <= 300; x++)									
		{
				//======================================		selekcja
				for (int i = 0; i < licznoscPopulacji / 2; i+=2)			
				{
					int a = populus[i].insta.czas_m1 < populus[i].insta.czas_m2 ? populus[i].insta.czas_m2 : populus[i].insta.czas_m1;
					int b = populus[i + 1].insta.czas_m1 < populus[i + 1].insta.czas_m2 ? populus[i + 1].insta.czas_m2 : populus[i + 1].insta.czas_m1;
					if (a < b)
					{
						tmp = new populacja;
						memcpy(tmp, &populus[i], sizeof(populacja));
						populus[i + 1] = *tmp;
						populus[i].najlepszeRozwiazanie = true;
					}
					else
					{
						tmp = new populacja;
						memcpy(tmp, &populus[i+1], sizeof(populacja));
						populus[i] = *tmp;
						populus[i].najlepszeRozwiazanie = true;
					}
				}

				//=====================================		przetasowanie
					for (int i = 0; i <= licznoscPopulacji / 2; i += 2)			
				{
					populacja temp;
					int a = rand() % licznoscPopulacji;
					int b = rand() % licznoscPopulacji;
					temp = populus[a];
					populus[a] = populus[b];
					populus[b] = temp;
				}

				//======================================	Mutacja
			int iloscMutacji = rand() % (int)(licznoscPopulacji*0.2) + (int)(licznoscPopulacji*0.1);
			for (int i = 0; i <= iloscMutacji; i += 2)					
			{
				//cout << "stoi na mutacji beg" << endl;
				int czynajlepsze = rand() % licznoscPopulacji;
				while (populus[czynajlepsze].najlepszeRozwiazanie == true)// nie chcemy zmienaic najlepszego rozwiazania
					czynajlepsze = rand() % licznoscPopulacji;
				populus[czynajlepsze].mutacja(oZad, oKonserwa);
				//cout << "stoi na mutacji end " << endl;
			}

			//=========================================		krzyzowanie
			int iloscCrossOver = licznoscPopulacji - iloscMutacji;
			for (int i = 0; i <= iloscCrossOver / 2; i += 2)			
			{
				//	cout << "stoi na krzyzowaniu beg" << endl;
				int a = rand() % licznoscPopulacji;
				int b = rand() % licznoscPopulacji;
			
				while (populus[a].najlepszeRozwiazanie == true)// nie chcemy zmienaic najlepszego rozwiazania
					a = rand() % licznoscPopulacji;
				while (populus[a].najlepszeRozwiazanie == true)// nie chcemy zmienaic najlepszego rozwiazania
					b = rand() % licznoscPopulacji;
				//	cout << "\n\t\tkrzyzowanie "<< a <<" z "<<b<<" przed: ";
				//	populus[a].wypisz();
				//	populus[b].wypisz();
				//	cout << "\t \t po";
				populus[a].krzyzowanie(populus[b], 1, oZad, oKonserwa);
				populus[a].krzyzowanie(populus[b], 2, oZad, oKonserwa);
				//	populus[a].wypisz();
				//	populus[b].wypisz();
				//	cout << "stoi na krzyzowaniu end" << endl;
			}
					
			//======================================		konczenie ewolucji
			for (int k = 0; k < licznoscPopulacji; k++)
			{
				populus[k].insta.wyliczCzas(oKonserwa, oZad);
				//	populus[k].wypisz();
				populus[k].najlepszeRozwiazanie = false;
			}

			//=====================================		poszukiwanie najlepszego rozwiazania
			najlepszeUszeregowanie(populus, najlepszeRozwiazanie,licznoscPopulacji,poczatkowaWartoscUporzadkowania);
			//cout << "\n\n Najlepsze rozwiazanie: \t\tm1: " << najlepszeRozwiazanie.insta.czas_m1 << "\t\tm2: " << najlepszeRozwiazanie.insta.czas_m2;
			
			
		//	_getch();
		//	system("cls");
			for (int i = 0; i <licznoscPopulacji; i++)//	sprawdzanie poprawnosci kazdego rozwiazania
				populus[i].insta.sprawdzPoprawnosc();
		
		}
		//=======================================		zapis
		zapisz(najlepszeRozwiazanie, filename, oKonserwa,licznoscPopulacji,poczatkowaWartoscUporzadkowania);
	}
	break;
	}
	cout << "zakonczono. nazwa pliku wynikowego to: wynik_NazwaPliku_pop_WielkoscPopulacji.txt";
	_getch();
	return 0;
}
//====================================================		fukncje
void wczytaj(vector<zad> &o1, vector < konserwacja> &o2, string filename,int ii)
{
	string buf,localFileName;
	fstream file;
	int ile1;
	zad tempZad;
	konserwacja tempKonserwa;
	localFileName= filename + ".txt";
	file.open(localFileName.c_str(), ios::in);
	if (!file.is_open())
		cout << "\nblad otwarcia pliku";
	else
	{
		getline(file, buf);
		ile1 = atoi(buf.c_str());
		ii = ile1;
		for (int i = 0; i < ile1; i++)
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

void zapisz(populacja populus,string filename, vector<konserwacja> oKonserwa, int licznosc,int startowa)
{
	int tempcalc = 0;;
	fstream file;
	string outfilename = "wynik_" + filename +"_pop_"+ to_string(licznosc)+".txt";
	file.open(outfilename.c_str(), ios::out);
	//===================================================	czas najlepszego uyszeregowania i czas 1 szeregowania
	if(populus.insta.czas_m1 > populus.insta.czas_m2)
	file <<   populus.insta.czas_m1 << "; ";
	else
		file<< populus.insta.czas_m2 << "; ";
	file << startowa;
	file << "\n";
	//==================================================	M1
	file << "M1: ";
	for (int i = 0; i < populus.ilewpopulacji; i++)
	{
		file << populus.insta.rozwiazanie[1][i].zadanie <<"op"<< populus.insta.rozwiazanie[1][i].operacja << " - ";
		file << populus.insta.czas[1][i].begin <<", "<< populus.insta.czas[1][i].time <<", "<< populus.insta.czas[1][i].end << "; ";
	}
	//==================================================	M2
	file << "\nM2: ";
	for (int i = 0; i < populus.ilewpopulacji; i++)
	{
		file <<  populus.insta.rozwiazanie[2][i].zadanie << "op" << populus.insta.rozwiazanie[2][i].operacja << " - ";
		file << populus.insta.czas[2][i].begin << ", " << populus.insta.czas[2][i].time << ", " << populus.insta.czas[2][i].end << "; ";
	}
	//================================================		przerwy konserwacyjne
	file << "\nLaczna_liczba_przerw_konserwacyjnych_M1: 0, ich_sumaryczny_czas_trwania: 0";
	for (int i = 0; i <= oKonserwa.size() - 1; i++) tempcalc += oKonserwa[i].time;
	file << "\nLaczna_liczba_przerw_konserwacyjnych_M2: " << oKonserwa.size() - 1 << ", ich_sumaryczny_czas_trwania: "<<tempcalc;
	//================================================		Przerwy typu iddle 
	tempcalc = 0;
	file << "\nLaczna_liczba_przerw_iddle_M1: 0, ich_sumaryczny_czas_trwania: 0";
	if (!populus.insta.czasCzekania.empty())
	{
		for (int i = 0; i <= populus.insta.czasCzekania.size() - 1; i++) tempcalc += populus.insta.czasCzekania[i].time;
		file << "\nLaczna_liczba_przerw_iddle_M2: " << populus.insta.czasCzekania.size()-1 << ", ich_sumaryczny_czas_trwania: " << tempcalc;
	}
	else
		file << "\nLaczna_liczba_przerw_iddle_M2: 0, ich_sumaryczny_czas_trwania: 0";


	file.close();
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
		
	}

}

void najlepszeUszeregowanie(vector<populacja> pointer, populacja &najlepsze, int liczebnosc, int &startowa)
{
	int kolejnosc;
	//===================		ktora z maszyn ma dluzszy czas ?
	if (pointer[0].insta.czas_m1 > pointer[0].insta.czas_m2)
		kolejnosc = 1;
	else kolejnosc = 2;
	//==================		poszukujemy najmniejszego czasu
	for (int i = 0; i < liczebnosc; i++)
	{
		if (kolejnosc == 1)
		{
			if (pointer[i].insta.czas_m1 <= najlepsze.insta.czas_m1)
				najlepsze = pointer[i];
		}
		else
		{
			if (pointer[i].insta.czas_m2 <= najlepsze.insta.czas_m2)
				najlepsze = pointer[i];
		}
	}
	if (kolejnosc == 1)
	{
		if (startowa == 0)
			startowa = najlepsze.insta.czas_m1;
	}
	else
		if (startowa == 0)
			startowa = najlepsze.insta.czas_m2;
		
}