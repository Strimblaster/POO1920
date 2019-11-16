#include "Piloto.h"

Piloto::Piloto(string nome)
{
	this->nome = nome;
}

string Piloto::getNome() const {
	return nome;
}

string Piloto::toString()
{
	return nome;
}

