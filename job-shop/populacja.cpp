#include "populacja.hpp"


populacja::populacja()
{
}

populacja::populacja(int ile)
{
}

void populacja::wczytaj(string name)
{

}

void populacja::inicializuj(vector<zad> &oZad, vector<konserwacja> oKonserwa)
{
	insta.inicjalizuj(oZad);
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

}
