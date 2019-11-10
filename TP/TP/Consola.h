#ifndef Consola_H
#define Consola_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "DGV.h"
#include <exception>

using namespace std;
class Consola
{
	DGV* dgv;
	bool nextCommand();
public:
	Consola(DGV*);
	void start();

};

#endif