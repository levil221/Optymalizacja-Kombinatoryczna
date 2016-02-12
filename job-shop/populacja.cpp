#include "populacja.hpp"
#include <assert.h>

populacja::populacja()
{
	najlepszeRozwiazanie = false;
}

void populacja::wypisz()
{
	insta.wyswietl();
}

void populacja::inicializuj(vector<zad> &oZad, vector<konserwacja> oKonserwa)
{
		ilewpopulacji = oZad.size() - 1;
	insta.inicjalizuj(oZad);
	for (int i = 0; i < oZad.size(); i++)
		oZad[i].czas_konca = 0;
	insta.wyliczCzas(oKonserwa,oZad,0,0);
	insta.poprawczasy(oZad, oKonserwa);
	//insta.wyswietl();
}

void populacja::krzyzowanie(populacja &b,int maszyna, vector<zad> &oZad, vector<konserwacja> oKonserwa)
{
	int *taba = new int[ilewpopulacji];
	int *tabb = new int[ilewpopulacji];
	task *tempTaska = new task[ilewpopulacji];
	task *tempTaskb = new task[ilewpopulacji];
	bool jest = false;
	
	
	// tworzenie kopi tablic i tablicy pomocnicznej mowiecej co jes a cczego nie ma================================================
	for (int i = 0; i < ilewpopulacji ; i++)// co mamy a czego nam brakuje
	{
		tempTaska[i] = this->insta.rozwiazanie[maszyna][i];//zapamietujemy co bedziemy zamieniac
		tempTaskb[i] = b.insta.rozwiazanie[maszyna][i];
		if (i < ilewpopulacji / 2)
		{
			taba[this->insta.rozwiazanie[maszyna][i].zadanie] = 1;//oznaczamy juz bedace na maszynie
			tabb[b.insta.rozwiazanie[maszyna][i].zadanie] = 1;
		}
		else
		{
			taba[this->insta.rozwiazanie[maszyna][i].zadanie] = 0;//tych nie ma na maszynie
			tabb[b.insta.rozwiazanie[maszyna][i].zadanie] = 0;
		}
	}
	//maszyna 1b ================================================================================================
	for (int i = ilewpopulacji / 2; i < ilewpopulacji; i++)
	{
		if (tabb[tempTaska[i].zadanie] == 0)//jak nie ma na maszynie to dodajemy
		{
			b.insta.rozwiazanie[maszyna][i] = tempTaska[i];
			tabb[tempTaska[i].zadanie] = 1;
			//cout << "\n" << tempTaska[i].zadanie <<" z "<< tempTaskb[i].zadanie;
		}
		else//jest na maszynie to musimy znalezsc jakiego zadania brakuje
		{
			for (int j = 0; j <= ilewpopulacji; j++)
			{
				jest = true;
				if (tabb[j] == 0)//szukamy brakujacego
					for (int x = ilewpopulacji / 2 ; x <= ilewpopulacji; x++)
						if (tempTaska[x].zadanie == j)//jak brakuje to srpawdzamy czy nie ma brakuajcego w liscie ktore zostana dodane
						{
							jest = true;//jak jest to szukamy nastepnego
							break;
						}
						else
							jest = false;
				if (!jest)//nie zostanie przenisiony z inengo roziazania
				{
					b.insta.rozwiazanie[maszyna][i] = tempTaskb[find2(j,maszyna,tempTaskb)];// to zostaje popsotu zadanie wpisane jakiego brakuje
					//cout << "\n" << tempTaska[i].zadanie << " z " << tempTaskb[i].zadanie;
					tabb[j] = 1;//no i zaznaczamy ze dodalismy
					break;
				}
			}
		}
		//maszyna 1a =============================================================================================
		if (taba[tempTaskb[i].zadanie] == 0)
		{
			this->insta.rozwiazanie[maszyna][i] = tempTaskb[i];
			taba[tempTaskb[i].zadanie] = 1;
			//cout << "\n" << tempTaskb[i].zadanie << " z " << tempTaska[i].zadanie;
		}
		else
		{
			for (int j = 0; j <= ilewpopulacji; j++)
			{
				jest = true;
				if (taba[j] == 0)
					for (int x = ilewpopulacji / 2 ; x <= ilewpopulacji; x++)
						if (tempTaskb[x].zadanie == j)
						{
							jest = true;
							break;
						}
						else
							jest = false;
				if (!jest)
				{
				//	cout << "\n\n" << b.find(j, maszyna);
					this->insta.rozwiazanie[maszyna][i] = tempTaska[b.find2(j,maszyna,tempTaska)];
				//	cout << "\n" << tempTaskb[i].zadanie << " z " << tempTaska[i].zadanie;
					taba[j] = 1;
					break;
				}
			}
		}
	}
	insta.ustawCzas(oZad);//musimy wyzerowac czasy bo kolejnsoc zadan inna
	insta.wyliczCzas(oKonserwa, oZad,0,0);//wyliczamy czasy
	if (!insta.czasCzekaniaM1.empty())//czyscimy wczesneij zapisane przerwy
		insta.czasCzekaniaM1.clear();
	if (!insta.czasCzekaniaM2.empty())//czyscimy wczesneij zapisane przerwy
		insta.czasCzekaniaM2.clear();
	insta.poprawczasy(oZad, oKonserwa);//poprawiamy czasy
//	insta.poprawczasy(oZad, oKonserwa);
	for (int i = 0; i < oZad.size(); i++)
		oZad[i].czas_konca = 0;
	//================================================ zwalnianie pamieci
	//delete[] taba;
	//delete[] tabb;
	//delete[] tempTaska;
	//delete[] tempTaskb;

}

void populacja::mutacja(vector<zad> &oZad, vector<konserwacja> oKonserwa)
{
	//cout << " weszlo do mutacji ";
	int a = rand() % ilewpopulacji +1,
		b = rand() % ilewpopulacji + 1,
		a1,a2,//indesky zad 1
		b1=-1,b2=-1,//indeksy zad 2
		operacja,losowanie=-1,losowaniea=-1,szukam=0;
	task taska1, taska2;//kopie zadania
	czasOperacji czasa1, czasa2;//kopie czasu
	int test;
	losowaniea = find(a, 1);
	while (szukam < 100)
	{
		if (losowaniea<0 || losowaniea > ilewpopulacji)
			losowaniea = find(a, 1);
		else
			break;
		szukam++;
	}
	szukam = 0;
      	if (insta.rozwiazanie[1][losowaniea].operacja == 1)//jezeli na maszynie 1 opecaja 1 to szukamy na maszynie 1 zadania ktore rowniez ma op1
	{
		a1 = find(a, 1);
		a2 = find(a, 2);
		while(a2>ilewpopulacji)
			a2 = find(a, 2);
		operacja = 1;
	}
	else {
		a2 = find(a, 2);
		a1 = find(a, 1);
		operacja = 2;
	}
	losowanie = find(b, 1);
	while (szukam < 100)
	{
		if (losowanie < 0 || losowanie > ilewpopulacji )
			losowanie = find(b, 1);
		else
			break;
		szukam++;
	}
if (insta.rozwiazanie[1][losowanie].operacja == operacja && a != b)// sprawdzamy czy wylosowane zadanie posiada ta sama operacje na tej maszynie
	{
		b1 = losowanie;
		for (int i = 0; i <= ilewpopulacji; i++)
			if (this->insta.rozwiazanie[2][i].zadanie == b)
			{
				b2 = i;
				break;
			}
		if (b2<0 || b2>ilewpopulacji)
			cout << "nie nzjaduje / !?";
	}else
			while (insta.rozwiazanie[1][losowanie].operacja != operacja )//szukaj az znajdzie
		{
		//	cout << " szuka az znajdzie -> mutacja ";
			b = rand() % (ilewpopulacji-1) + 1;
			while(a==b)
				b = rand() % (ilewpopulacji-1) + 1;
			for (int i = 0; i <= ilewpopulacji; i++)
				if (this->insta.rozwiazanie[1][i].zadanie == b)
				{
					losowanie = i;
					break;
				}

			
			
		}
	if (insta.rozwiazanie[1][losowanie].operacja == operacja)
	{
		b1 = losowanie;
		for (int i = 0; i <= ilewpopulacji; i++)
			if (this->insta.rozwiazanie[2][i].zadanie == b)
			{
				b2 = i;
				break;
			}

		if (b2<0 || b2>ilewpopulacji)
			cout << "nie nzjaduje / !?";
	}
	//assert(ilewpopulacji > b2 < 0);
	//insta.wyswietl();//przed zmianmi
	//====================================================		zamieniamy
	//	cout << "\n zamiamiany na m1: " << insta.rozwiazanie[1][a1].zadanie << " z " << insta.rozwiazanie[1][losowanie].zadanie << endl;
	//	cout << " zamiamiany na m2: " << insta.rozwiazanie[2][a2].zadanie << " z " << insta.rozwiazanie[2][b2].zadanie << endl;
	//do tempa temp=a
	taska1 = insta.rozwiazanie[1][a1];
	czasa1 = insta.czas[1][a1];
	taska2 = insta.rozwiazanie[2][a2];
	czasa2 = insta.czas[2][a2];
	//===============================================		nadpisanie a=b
	//cout << "\ndochodzi do nadpisania\n";
	insta.rozwiazanie[1][a1] = insta.rozwiazanie[1][losowanie];
	insta.czas[1][a1] = insta.czas[1][losowanie];
	insta.rozwiazanie[2][a2] = insta.rozwiazanie[2][b2];
	insta.czas[2][a2] = insta.czas[2][b2];
	//==============================================		zastapienie b=temp
	insta.rozwiazanie[1][losowanie] = taska1;
	insta.czas[1][losowanie] = czasa1;
	insta.rozwiazanie[2][b2] = taska2;
	insta.czas[2][b2] = czasa2;
	insta.ustawCzas(oZad);				//zerujemy ustawienie czasu
	insta.wyliczCzas(oKonserwa,oZad,0,0);   // wyliczamy czasy po zeriwaniu
	if (!insta.czasCzekaniaM1.empty())//czyscimy wczesneij zapisane przerwy
		insta.czasCzekaniaM1.clear();
	if (!insta.czasCzekaniaM2.empty())//czyscimy wczesneij zapisane przerwy
		insta.czasCzekaniaM2.clear();
	insta.poprawczasy(oZad, oKonserwa);//naprawiamy czasy

	//insta.poprawczasy(oZad, oKonserwa);
	//insta.wyswietl();
	//==============================================		po zmianie
	for (int i = 0; i < oZad.size(); i++)
		oZad[i].czas_konca = 0;

}

int populacja::find(int zadanie,int maszyna)//szukamy indeksu podanego zadania na podanej maszynie
{
	for (int i = 0; i <= ilewpopulacji; i++)
		if (this->insta.rozwiazanie[maszyna][i].zadanie == zadanie)
			return i;
}

int populacja::find2(int zadanie, int maszyna, task *roz)
{
	for (int i = 0; i < ilewpopulacji; i++)
		if (roz[i].zadanie == zadanie)
			return i;
}

