#include "Piloto.h"

Piloto::Piloto(string nome, vector<Piloto*> pilotos)
{
	for (int i = 0; i < pilotos.size(); i++)
		if (pilotos.at(i)->getNome() == nome) {
			nome += "1";
			i = -1;
		}

	this->nome = nome;
}

string Piloto::getNome() const {
	return nome;
}

string Piloto::toString()
{
	return nome;
}

