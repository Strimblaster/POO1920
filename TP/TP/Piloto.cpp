#include "Piloto.h"
#include <sstream>

Piloto::Piloto(string nome, vector<Piloto*> pilotos)
{
	for (unsigned int i = 0; i < pilotos.size(); i++)
		if (pilotos.at(i)->getNome() == nome) {
			nome += "1";
			i = -1;
		}

	this->nome = nome;
	this->tipo = "Generico";
}

string Piloto::getNome() const {
	return nome;
}

string Piloto::toString()
{
	ostringstream oss;
	oss << tipo << " " << nome;
	return oss.str();
}

int Piloto::mover(float energia, int capacidadeMax, int posicao, int nCarros)
{
	if (energia == 0) return 0;
	return 1;
}

