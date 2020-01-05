#include "Piloto.h"
#include <sstream>
#include "Carro.h"

Piloto::Piloto(string nome, vector<Piloto*> pilotos, string tipo)
{
	for (unsigned int i = 0; i < pilotos.size(); i++)
		if (pilotos.at(i)->getNome() == nome) {
			nome += "1";
			i = -1;
		}

	this->nome = nome;
	this->tipo = tipo;
	parar = false;
}

void Piloto::reset()
{
	parar = false;
}

string Piloto::getNome() {
	return nome;
}

string Piloto::getTipo()
{
	return tipo;
}

bool Piloto::getParar()
{
	return parar;
}

void Piloto::para()
{
	parar = true;
}

string Piloto::toString()
{
	ostringstream oss;
	oss << tipo << " " << nome << " " << tipo;
	return oss.str();
}

int Piloto::mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida)
{
	return 1;
}

