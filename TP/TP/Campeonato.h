#include "Autodromo.h"
#include <map>
#include <sstream>
#ifndef Campeonato_H
#define Campeonato_H

using namespace std;
class Campeonato
{
	vector<Autodromo*>* pistas;
	map<Piloto*, int> pontuacao;
	vector<Carro*> carros;
	int corridaAtual;
	int corridaAnterior;
	void moveCarros(Autodromo*, Autodromo*);

public:
	Campeonato(vector<Autodromo*>, vector<Piloto*>, vector<Carro*>);
	~Campeonato();

	string scoreboard();
	bool proximaCorrida();
	string infoCampeonato();

	string getGaragem();
	vector<Via*> getPosicoes();
	int getLargura();
	int getComprimento();
	bool passaTempo();
	bool partidaADecorrer();
	string listaCarros();
};


#endif
