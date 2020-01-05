#include "Via.h"
#include "Piloto.h"

Via::Via(Carro* carro, int pista, int comprimento)
{
	this->carro = carro;
	this->posicao = 0;
	this->pista = pista;
	this->tempo = 0;
	this->comprimento = comprimento;
}

Carro* Via::getCarro()
{
	return carro;
}

int Via::getPosicao()
{
	return posicao;
}

int Via::getPista()
{
	return pista;
}

int Via::getTempo()
{
	return tempo;
}

void Via::mover(int comp, int pos, int nCarros)
{
	Piloto* piloto = carro->getPiloto();
	bool finalDacorrida = posicao / (float)comprimento > 0.75;
	posicao += piloto->mover(carro, pos, nCarros, finalDacorrida);
	if (posicao >= comprimento) {
		posicao = comprimento;
	}
	tempo++;
}

Via& Via::operator+=(const int i) {
	posicao += i;
	return *this;
}
