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
void zapisz(populacja *populus, string filename, vector<konserwacja> oKonserwa,int licznosc,int startowa1, int startowa2);
void najlepszeUszeregowanie(vector<populacja> pointer, populacja &najlepsze,int liczebnosc, int &startowa1, int &startowa2,int &poczatek);

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
		int licznoscPopulacji, poczatkowaWartoscUporzadkowaniam1 = 999999, poczatkowaWartoscUporzadkowaniam2 = 999999,poczatkoweUszeregowanie=0;
		vector<populacja> populus;
		populacja *tmp, *najlepszeRozwiazanie = new populacja;
		najlepszeRozwiazanie->insta.czas_m1 = 999999;
		najlepszeRozwiazanie->insta.czas_m2 = 999999;

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
			//delete tmp;
			populus[i].inicializuj(oZad, oKonserwa);
			populus[i].insta.sprawdzPoprawnosc();
		//	populus[i].wypisz();
			cout << i << endl;
		}
		najlepszeUszeregowanie(populus, *najlepszeRozwiazanie, licznoscPopulacji, poczatkowaWartoscUporzadkowaniam1, poczatkowaWartoscUporzadkowaniam2,poczatkoweUszeregowanie);//najlepsze losowe uszeregowanie
		//===============================================		Ewolucja
		for (int x =0; x <= 500; x++)									
		{
				//======================================		selekcja
				for (int i = 0; i < licznoscPopulacji / 2; i+=2)			
				{
					int a = populus[i].insta.czas_m1 < populus[i].insta.czas_m2 ? populus[i].insta.czas_m2 : populus[i].insta.czas_m1;
					int b = populus[i + 1].insta.czas_m1 < populus[i + 1].insta.czas_m2 ? populus[i + 1].insta.czas_m2 : populus[i + 1].insta.czas_m1;
					if (a < b)
					{
						tmp = new populacja(populus[i]);
						populus[i + 1] = *tmp;
						populus[i].najlepszeRozwiazanie = true;
						//delete tmp;
					}
					else
					{
						tmp = new populacja(populus[i+1]);
						populus[i] = *tmp;
						populus[i].najlepszeRozwiazanie = true;
						//delete tmp;
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
				int zapetlenie = 0;
				cout << "stoi na mutacji beg" << endl;
				int czynajlepsze = rand() % licznoscPopulacji;
				while (populus[czynajlepsze].najlepszeRozwiazanie == true|| zapetlenie <1000)// nie chcemy zmienaic najlepszego rozwiazania
				{
					czynajlepsze = rand() % licznoscPopulacji;
					zapetlenie++;
					//cout << " " << zapetlenie;
				}
				populus[czynajlepsze].mutacja(oZad, oKonserwa);
				//cout << "stoi na mutacji end " << endl;
			}

			//=========================================		krzyzowanie
			int iloscCrossOver = licznoscPopulacji - iloscMutacji;
			for (int i = 0; i <= iloscCrossOver / 2; i += 2)			
			{
				cout << "stoi na krzyzowaniu beg" << endl;
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
					cout << "stoi na krzyzowaniu end" << endl;
			}
					
			//======================================		konczenie ewolucji
			for (int k = 0; k < licznoscPopulacji; k++)
			{
				populus[k].insta.sprawdzPoprawnosc(); // sprawdzanie poprawosciu
				//populus[k].insta.wyliczCzas(oKonserwa, oZad);
				//populus[k].wypisz();
				populus[k].najlepszeRozwiazanie = false;
			}

			//=====================================		poszukiwanie najlepszego rozwiazania
			najlepszeUszeregowanie(populus, *najlepszeRozwiazanie, licznoscPopulacji,poczatkowaWartoscUporzadkowaniam1, poczatkowaWartoscUporzadkowaniam2,poczatkoweUszeregowanie);
			//najlepszeRozwiazanie->wypisz();
			//cout << "\n\n Najlepsze rozwiazanie: \t\tm1: " << najlepszeRozwiazanie.insta.czas_m1 << "\t\tm2: " << najlepszeRozwiazanie.insta.czas_m2;
			
			
			//_getch();
			//system("cls");
			//for (int i = 0; i <licznoscPopulacji; i++)//	sprawdzanie poprawnosci kazdego rozwiazania
			//	populus[i].insta.sprawdzPoprawnosc();
		
		}
		//=======================================		zapis
		zapisz(najlepszeRozwiazanie, filename, oKonserwa,licznoscPopulacji,poczatkowaWartoscUporzadkowaniam1, poczatkowaWartoscUporzadkowaniam2);
		
		
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

void zapisz(populacja *populus,string filename, vector<konserwacja> oKonserwa, int licznosc,int startowa1,int startowa2)
{
	int tempcalc = 0;;
	fstream file;
	string outfilename = "wynik_" + filename +"_pop_"+ to_string(licznosc)+".txt";
	file.open(outfilename.c_str(), ios::out);
	//===================================================	czas najlepszego uyszeregowania i czas 1 szeregowania
	if (populus->insta.czas_m1 > populus->insta.czas_m2)
	{
		file << populus->insta.czas_m1 << "; ";
		file << startowa1;
	}
	else
	{
		file << populus->insta.czas_m2 << "; ";
		file << startowa2;
	}
	
	file << "\n";
	//==================================================	M1
	file << "M1: ";
	for (int i = 0; i <licznosc; i++)
	{
		file << populus->insta.rozwiazanie[1][i].zadanie <<"op"<< populus->insta.rozwiazanie[1][i].operacja << " - ";
		file << populus->insta.czas[1][i].begin <<", "<< populus->insta.czas[1][i].time <<", "<< populus->insta.czas[1][i].end << "; ";
	}
	//==================================================	M2
	file << "\nM2: ";
	for (int i = 0; i < licznosc; i++)
	{
		file <<  populus->insta.rozwiazanie[2][i].zadanie << "op" << populus->insta.rozwiazanie[2][i].operacja << " - ";
		file << populus->insta.czas[2][i].begin << ", " << populus->insta.czas[2][i].time << ", " << populus->insta.czas[2][i].end << "; ";
	}
	//================================================		przerwy konserwacyjne
	file << "\nLaczna_liczba_przerw_konserwacyjnych_M1: 0, ich_sumaryczny_czas_trwania: 0";// 0 bo w zadaniuu sa tylko na 2
	for (int i = 0; i <= oKonserwa.size() - 1; i++) tempcalc += oKonserwa[i].time;
	file << "\nLaczna_liczba_przerw_konserwacyjnych_M2: " << oKonserwa.size() - 1 << ", ich_sumaryczny_czas_trwania: "<<tempcalc;
	//================================================		Przerwy typu iddle 
	tempcalc = 0;
	if (!populus->insta.czasCzekaniaM1.empty())
	{
		for (int i = 0; i < populus->insta.czasCzekaniaM1.size() ; i++) tempcalc += populus->insta.czasCzekaniaM1[i].time;
		file << "\nLaczna_liczba_przerw_iddle_M1: " << populus->insta.czasCzekaniaM1.size()  << ", ich_sumaryczny_czas_trwania: " << tempcalc;
	}
	else
		file << "\nLaczna_liczba_przerw_iddle_M1: 0, ich_sumaryczny_czas_trwania: 0";
	tempcalc = 0;
	if (!populus->insta.czasCzekaniaM2.empty())
	{
		for (int i = 0; i < populus->insta.czasCzekaniaM2.size() ; i++) tempcalc += populus->insta.czasCzekaniaM2[i].time;
		file << "\nLaczna_liczba_przerw_iddle_M2: " << populus->insta.czasCzekaniaM2.size() << ", ich_sumaryczny_czas_trwania: " << tempcalc;
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

void najlepszeUszeregowanie(vector<populacja> pointer, populacja &najlepsze, int liczebnosc, int &startowa1, int &startowa2,int &poczatek)
{
	
	//==================		poszukujemy najmniejszego czasu
	for (int i = 0; i < liczebnosc; i++)
	{
		int a; int b;
		if (pointer[i].insta.czas_m1 < pointer[i].insta.czas_m2)
		{
			a = pointer[i].insta.czas_m2;
			poczatek += 1;
		}
		else
		{
			a = pointer[i].insta.czas_m1;
			poczatek += 1;
		}
		
		if (najlepsze.insta.czas_m1 < najlepsze.insta.czas_m2)
		{
			b = najlepsze.insta.czas_m2;
			poczatek += 1;
		}
		else
		{
			b = najlepsze.insta.czas_m1;
			poczatek += 1;
		}
		if (a < b)
		{

			populacja *nowy = new populacja(pointer[i]);
			najlepsze = *nowy;
			/*if (najlepsze.insta.czas_m1 != najlepsze.insta.czas[1][liczebnosc - 2].end)
			{
				najlepsze.insta.czas_m1 = najlepsze.insta.czas[1][liczebnosc - 2].end;//bledne obliczenie czasu, wiec naprawiamy
			}
			if (najlepsze.insta.czas_m2 != najlepsze.insta.czas[2][liczebnosc - 2].end)
			{
				najlepsze.insta.czas_m2 = najlepsze.insta.czas[2][liczebnosc - 2].end;//bledne obliczenie czasu, wiec naprawiamy
			}*/
		}
		if (poczatek < liczebnosc)
		{
			startowa1 = najlepsze.insta.czas_m1;
			startowa2 = najlepsze.insta.czas_m2;
		}
	}
}