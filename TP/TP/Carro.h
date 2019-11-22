#ifndef Carro_H
#define Carro_H

#include <string>
#include "Piloto.h"

using namespace std;

class Carro {
	static int contador;

	char id;
	string marca,modelo;
	int velocidade;
	float energia;
	Piloto* piloto;
	bool sinalEmergencia;

	const int capacidadeMax;
	const int velocidadeMax;
public:
	enum Estado {
		movimento,
		parado,
		danificado
	};
	Estado estado;
	Carro(string marca, int capacidadeMax, int energiaInicial, int velocidadeMax, string modelo = "Base");
	void acelerar();
	void travar();
	int mover();
	void entrarPiloto(Piloto* p);
	string toString();
	const char getid();
	Piloto* getPiloto();
	void sairPiloto();
	

};


#endif