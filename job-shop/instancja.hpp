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
	

	void inicjalizuj(vector<zad> oZad);
	void wyliczCzas(vector<konserwacja> oKonserwa, vector<zad> &oZad);
	void wyswietl();
	void update(int start, vector<zad> &oZad);
	instancja();
	
};