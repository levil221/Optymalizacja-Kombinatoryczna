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
public:
	populacja();
	populacja(int ile);

	void wczytaj(string name);
	void inicializuj(vector<zad> &oZad, vector<konserwacja> oKonserwa);
	void krzyzowanie(instancja &b);
	void mutacja();
	

};