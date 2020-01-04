#include "Carro.h"
#ifndef Piloto_H
#define Piloto_H

#include <string>
#include <vector>


using namespace std;
class Piloto
{
	string nome;

protected:
	string tipo;

public:
	Piloto(string, vector<Piloto*>);

	string getNome() const;
	string toString();
	virtual int mover(float energia, int capacidadeMax, int posicao, int nCarros);
};

#endif