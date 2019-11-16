#include "Carro.h"
#include <vector>
#include <map>

#ifndef Autodromo_H
#define Autodromo_H
using namespace std;
class Autodromo
{
	vector<Carro*> garagem;
	map<Carro*, int> posicao;
	const int largura;
	const int comprimento;
	string nome;

public:
	Autodromo(string, int, int);
	string getNome();
};
#endif
