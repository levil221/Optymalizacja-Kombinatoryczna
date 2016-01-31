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
	for (int i = 0; i < oZad.size(); i++)
		oZad[i].czas_konca = 0;
	insta.wyswietl();
}

void populacja::krzyzowanie(instancja &b)
{
}

void populacja::mutacja()
{
	int a = rand() % ilewpopulacji +1,
		b = rand() % ilewpopulacji + 1,
		a1,a2,
		b1,b2,
		operacja,losowanie;
	task taska1, taska2;

	if (insta.rozwiazanie[1][find(a, 1)].operacja == 1)//jezeli na maszynie 1 opecaja 1 to szukamy na maszynie 1 zadania ktore rowniez ma op1
	{
		a1 = find(a, 1);
		b2 = find(a, 2);
		operacja = 1;
	}
	else {
		a2 = find(a, 2);
		a1 = find(a, 1);
		operacja = 2;
	}
	losowanie = find(b, 1);
	while (insta.rozwiazanie[1][losowanie].operacja != operacja)
	{
		b = rand() % ilewpopulacji + 1;
		losowanie = find(b, 1);
		if (insta.rozwiazanie[1][find(b, 1)].operacja == 1)
		{
			a1 = find(b, 1);
			b2 = find(b, 2);
		}
	}
	
	
}

int populacja::find(int zadanie,int maszyna)
{
	for (int i = 0; i <= ilewpopulacji; i++)
		if (insta.rozwiazanie[maszyna][i].zdanie == zadanie)
			return i;
}
