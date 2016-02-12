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
	bool najlepszeRozwiazanie;
public:
	populacja();
	populacja(const populacja &do_skopiowania);
	void wypisz();
	void inicializuj(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	void krzyzowanie(populacja &b, int maszyna, vector<zad> &oZad, vector<konserwacja> oKonserwa);
	void mutacja(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	int find(int zadanie, int maszyna);
	int find2(int zadanie, int maszyna, task *roz);
};