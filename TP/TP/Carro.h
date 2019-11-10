#ifndef Carro_H
#define Carro_H

#include <string>
#include "Piloto.h"

using namespace std;

class Carro {
	enum estado {
		movimento,
		parado,
		danificado
	};

	static int contador;

	char id;
	string marca,modelo;
	estado estado;
	int velocidade;
	float energia;
	Piloto* piloto;
	bool sinalEmergencia;

	const int capacidadeMax;
	const int velocidadeMax;
public:
	Carro(string marca, string modelo, int capacidadeMax, int energiaInicial, int velocidadeMax);
	void acelerar();
	void travar();
	void mover();
	void entrarPiloto(Piloto* p);
	string toString();

		
};


#endif