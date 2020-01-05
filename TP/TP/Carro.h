#ifndef Carro_H
#define Carro_H

#include <string>

using namespace std;
class Piloto;
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
	int acelerar(int n = 1);
	int travar();
	int manterVelocidade();
	void gastaEnergia();
	void ativarSinalEmergencia();
	void reset();
	int getVelocidade();
	float getEnergia();
	bool getSinalEmergencia();
	int getEnergiaMax();
	void entrarPiloto(Piloto* p);
	string toString();
	const char getid();
	Piloto* getPiloto();
	void sairPiloto();
	void setVel(int v);
	void carrega(int n);
	void danificar();
	void carregaTudo();
	string toStringBoard();

};


#endif