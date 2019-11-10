#ifndef Jogo_H
#define Jogo_H

#include "Carro.h"
#include <vector>
#include <sstream>

using namespace std;

class Jogo
{
	vector<Piloto> pilotos;
	vector<Carro> carros;
	void addPiloto(Piloto);
	void addCarro(Carro);
public:

	Jogo();
	void cria(vector<string>);
	string listaCarros();
};

#endif
