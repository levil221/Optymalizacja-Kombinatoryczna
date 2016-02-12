#pragma once
#include <iostream>
#include <vector>
#include<time.h>
#include <stdlib.h>
#include "struktury.hpp"
using namespace std;

class instancja
{
public:
	int czas_m1,
		czas_m2,
		nr,
		ile;
	task **rozwiazanie;
	czasOperacji **czas;
	vector<iddleTime> czasCzekaniaM2;
	vector<iddleTime> czasCzekaniaM1;

	void inicjalizuj(vector<zad> oZad);
	void wyliczCzas(vector<konserwacja> oKonserwa, vector<zad> &oZad,int i,int _czasm2);
	void wyswietl();
	void update(int start, vector<zad> &oZad);
	int findIndex(int zadanie, int maszyna);
	void ustawCzas(vector<zad> &oZad);
	void sprawdzPoprawnosc();
	void poprawczasy(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	instancja();
	instancja(const instancja &do_skopiowania);
	~instancja();
	
};