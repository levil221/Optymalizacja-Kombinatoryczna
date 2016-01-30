#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include "struktury.hpp"
using namespace std;

class generator
{
public:
	int ilosc_zadan,
		ilosc_przerw,
		czas_m1,
		czas_m2;
	fstream file;
	string filename;
	vector<zad> zadanie;
	vector<konserwacja> przerwy;
	
	void generujPrzerwy();
	void generujZadania();
	void getTime();
	void zapisz();

	generator();
	generator(string name,int ile);

};
