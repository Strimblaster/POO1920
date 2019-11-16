#ifndef DGV_H
#define DGV_H

#include "Carro.h"
#include <vector>
#include <sstream>
#include "Autodromo.h"
#include "Campeonato.h"

using namespace std;

class DGV
{
	vector<Piloto*> pilotos;
	vector<Carro*> carros;
	vector<Autodromo*> autodromos;
	Campeonato* campeonato;

	void addPiloto(Piloto*);
	void addCarro(Carro*);
	void addAutodromo(Autodromo*);
	string listaPilotos();
	string listaCarros();
public:

	DGV();
	void cria(vector<string>);	
	string lista();
	void entraNoCarro(vector<string>);
	void saiDoCarro(vector<string>);
	void comandoCampeonato(vector<string> comando);
};
#endif
