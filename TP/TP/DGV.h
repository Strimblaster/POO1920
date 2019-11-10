#ifndef DGV_H
#define DGV_H

#include "Carro.h"
#include <vector>
#include <sstream>
#include "Autodromo.h"

using namespace std;

class DGV
{
	vector<Piloto> pilotos;
	vector<Carro> carros;
	vector<Autodromo> autodromos;

	void addPiloto(Piloto);
	void addCarro(Carro);
	void addAutodromo(Autodromo);
public:

	DGV();
	void cria(vector<string>);
	string listaCarros();
};
#endif
