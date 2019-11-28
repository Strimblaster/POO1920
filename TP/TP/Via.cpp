#include "Via.h"

Via::Via(Carro* carro, int pista)
{
	this->carro = carro;
	this->posicao = 0;
	this->pista = pista;
	this->tempo = 0;
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

void Via::mover(int comp)
{
	posicao += carro->mover();
	if (posicao > comp)
		posicao = comp;
	tempo++;
}

Via& Via::operator+=(const int i) {
	posicao += i;
	return *this;
}
