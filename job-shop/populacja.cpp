#include "populacja.hpp"


populacja::populacja()
{
}

populacja::populacja(int ile)
{
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
	insta.wyliczCzas(oKonserwa,oZad);
	//insta.wyswietl();
}

void populacja::krzyzowanie(instancja &b,int maszyna)
{
	int *taba = new int[ilewpopulacji];
	int *tabb = new int[ilewpopulacji];
	task *tempTaska = new task[ilewpopulacji];
	task *tempTaskb = new task[ilewpopulacji];
	bool jest = false;

	for (int i = 0; i <= ilewpopulacji ; i++)// co mamy a czego nam brakuje
	{
		if (i <= ilewpopulacji / 2)
		{
			taba[this->insta.rozwiazanie[maszyna][i].zadanie] = 1;
			tabb[b.rozwiazanie[maszyna][i].zadanie] = 1;
		}
		else
		{
			taba[this->insta.rozwiazanie[maszyna][i].zadanie] = 0;
			tabb[b.rozwiazanie[maszyna][i].zadanie] = 0;
			tempTaska[i] = this->insta.rozwiazanie[maszyna][i];//zapamietujemy co bedziemy zamieniac
			tempTaskb[i] = b.rozwiazanie[maszyna][i];
		}
	}

	for (int i = ilewpopulacji / 2 + 1; i <= ilewpopulacji; i++)
	{
		if (tabb[tempTaska[i].zadanie] == 0)
			b.rozwiazanie[maszyna][i] = tempTaska[i];
		else
		{
			for (int j = 0; j <= ilewpopulacji; j++)
			{
				jest = false;
				if (tabb[j] == 0)
					for (int x = ilewpopulacji / 2 + 1; i < ilewpopulacji; i++)
						if (tempTaska[x].zadanie == j)
						{
							jest = true;
							break;
						}
						else
							jest = false;
				if (!jest)
				{
					b.rozwiazanie[maszyna][i] = tempTaska[j];
					break;
				}
			}
		}

		if (taba[tempTaskb[i].zadanie] == 0)
			this->insta.rozwiazanie[maszyna][i] = tempTaskb[i];
		else
		{
			for (int j = 0; j <= ilewpopulacji; j++)
			{
				jest = false;
				if (taba[j] == 0)
					for (int x = ilewpopulacji / 2 + 1; i < ilewpopulacji; i++)
						if (tempTaskb[x].zadanie == j)
						{
							jest = true;
							break;
						}
						else
							jest = false;
				if (!jest)
				{
					this->insta.rozwiazanie[maszyna][i] = tempTaskb[j];
					break;
				}
			}
		}
	}
	
}

void populacja::mutacja(vector<zad> &oZad, vector<konserwacja> oKonserwa)
{
	int a = rand() % ilewpopulacji +1,
		b = rand() % ilewpopulacji + 1,
		a1,a2,//indesky
		b1,b2,//indeksy
		operacja,losowanie;
	task taska1, taska2;//kopia zadania
	czasOperacji czasa1, czasa2;//kopia czasu

	if (insta.rozwiazanie[1][find(a, 1)].operacja == 1)//jezeli na maszynie 1 opecaja 1 to szukamy na maszynie 1 zadania ktore rowniez ma op1
	{
		a1 = find(a, 1);
		a2 = find(a, 2);
		operacja = 1;
	}
	else {
		a2 = find(a, 2);
		a1 = find(a, 1);
		operacja = 2;
	}
	losowanie = find(b, 1);
	if (insta.rozwiazanie[1][losowanie].operacja == operacja&& a != b)
	{
		b1 = losowanie;
		b2 = find(b,2);
	}else
			while (insta.rozwiazanie[1][losowanie].operacja != operacja )
		{
			b = rand() % ilewpopulacji + 1;
			while(a==b)
				b = rand() % ilewpopulacji + 1;
			losowanie = find(b, 1);
			if (insta.rozwiazanie[1][losowanie].operacja == operacja)
			{
				b1 = losowanie;
				b2 = find(b,2);
			}
		}
	insta.wyswietl();//przed zmianmi
	//zamieniamy
	cout << "\n zamiamiany na m1: " << insta.rozwiazanie[1][a1].zdanie << " z " << insta.rozwiazanie[1][b1].zdanie << endl;
	cout << " zamiamiany na m2: " << insta.rozwiazanie[2][a2].zdanie << " z " << insta.rozwiazanie[2][b2].zdanie << endl;
	//do tempa
	taska1 = insta.rozwiazanie[1][a1];
	czasa1 = insta.czas[1][a1];
	taska2 = insta.rozwiazanie[2][a2];
	czasa2 = insta.czas[2][a2];
	//nadpisanie
	insta.rozwiazanie[1][a1] = insta.rozwiazanie[1][b1];
	insta.czas[1][a1] = insta.czas[1][b1];
	insta.rozwiazanie[2][a2] = insta.rozwiazanie[2][b2];
	insta.czas[2][a2] = insta.czas[2][b2];
	//zastapienie
	insta.rozwiazanie[1][b1] = taska1;
	insta.czas[1][b1] = czasa1;
	insta.rozwiazanie[2][b2] = taska2;
	insta.czas[2][b2] = czasa2;
	insta.update(0,oZad);
	insta.wyliczCzas(oKonserwa,oZad);
	insta.wyswietl();// po zmianie


}

int populacja::find(int zadanie,int maszyna)
{
	for (int i = 0; i <= ilewpopulacji; i++)
		if (insta.rozwiazanie[maszyna][i].zadanie == zadanie)
			return i;
}


