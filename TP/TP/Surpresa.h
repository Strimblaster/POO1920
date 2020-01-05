#ifndef Surpresa_H
#define Surpresa_H

#include "Piloto.h"
class Surpresa :public Piloto
{
	//nos 25% finais da pista ativa o turbo e acelera 3m/s
	//ou se tiver em ultimo, nesses 25% finais, desiste e ativa o botão de emergencia
public:
	Surpresa(string, vector<Piloto*>);
	int mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida) override;
};

#endif