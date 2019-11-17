#include "Carro.h"
#include <vector>
#include <map>
#include <sstream>

#ifndef Autodromo_H
#define Autodromo_H
using namespace std;
class Autodromo
{
	vector<Carro*> garagem;
	map<Carro*, int> posicoes;
	const int largura;
	const int comprimento;
	string nome;

public:
	Autodromo(string, int, int, vector<Autodromo*>);
	string getNome();
	int getLargura();
	int getComprimento();
	string toString();
	void autodromoController(Carro*);
	string getGaragem();
	map<Carro*, int> getPosicoes();
	bool passaTempo();
	bool gameEnded();
	vector<Piloto*> getTop3();
	

};
#endif
