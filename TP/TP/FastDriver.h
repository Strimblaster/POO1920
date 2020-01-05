#ifndef FastDriver_H
#define FastDriver_H

#include "Piloto.h"
class FastDriver : public Piloto
{
	int contadorEnergia;
	int contadorAnsiedade;
public:
	FastDriver(string, vector<Piloto*>);
	int mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida) override;
	void reset() override;

};

#endif