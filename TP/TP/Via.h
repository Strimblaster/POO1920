#include "Carro.h"

#ifndef Via_H
#define Via_H
class Via
{
	Carro* carro;
	int posicao;
	int pista;
	int tempo;
	int comprimento;

public:
	Via(Carro* carro, int pista, int comprimento);

	Carro* getCarro();
	int getPosicao();
	int getPista();
	int getTempo();
	void mover(int comp, int pos, int nCarros);

	Via& operator+=(const int i);
};




#endif

