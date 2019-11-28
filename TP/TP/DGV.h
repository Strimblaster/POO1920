#ifndef DGV_H
#define DGV_H

#include "Carro.h"
#include <vector>
#include <sstream>
#include "Autodromo.h"
#include "Campeonato.h"
#include "CrazyDriver.h"
#include "FastDriver.h"

using namespace std;

class DGV
{
	vector<Piloto*> pilotos;
	vector<Carro*> carros;
	vector<Autodromo*> autodromos;
	Campeonato* campeonato;

	void addPiloto(Piloto*);
	void addCarro(Carro*);
	void addAutodromo(vector<string> comando);
	string listaPilotos();
	string listaCarros();
	string listaAutodromos();
public:

	DGV();
	~DGV();
	void cria(vector<string>);	
	string lista();
	void entraNoCarro(vector<string>);
	void saiDoCarro(vector<string>);
	void comandoCampeonato(vector<string> comando);
	int getLargura();
	int getComprimento();
	void infoCampeonato();
	void scoreboard();
	string getGaragem();
	vector<Via*> getPosicoes();
	bool passaTempo();
	bool corridaADecorrer();
	bool proxCorrida();
	string listaCarrosCampeonato();
	void apaga(vector<string>);
	void carregaP(vector<string>);
	void carregaC(vector<string>);
	void carregaA(vector<string>);


};
#endif
