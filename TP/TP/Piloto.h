#ifndef Piloto_H
#define Piloto_H

#include <string>
#include <vector>
#include <sstream>


using namespace std;

class Carro;
class Piloto
{
	string nome;
	string tipo;
	bool parar;

public:
	Piloto(string, vector<Piloto*>, string);

	virtual void reset();
	string getNome();
	string getTipo();
	bool getParar();
	void para();
	virtual string toString();
	virtual int mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida);
};

#endif