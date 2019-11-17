#ifndef Consola_H
#define Consola_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "DGV.h"
#include <exception>

using namespace std;
class Consola
{
	DGV* dgv;
	int modo;
	bool nextCommand();
	void desenharPista(int comprimento, int largura);
public:
	Consola(DGV*);
	void start();
	bool passatempo(vector<string>);
};

#endif