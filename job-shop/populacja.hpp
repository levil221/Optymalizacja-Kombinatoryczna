#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "instancja.hpp"
#include"instancja.hpp"
#include"struktury.hpp"
using namespace std;

class populacja
{
public:
	instancja insta;
	int ilewpopulacji;
public:
	populacja();
	populacja(int ile);

	void wypisz();
	void inicializuj(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	void krzyzowanie(instancja &b,int maszyna);
	void mutacja(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	int find(int zadanie,int maszyna);
	
};