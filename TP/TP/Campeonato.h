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

public:
	Campeonato(vector<Autodromo*>, vector<Piloto*>, vector<Carro*>);

	string scoreboard();
	void proximaCorrida();

};


#endif
