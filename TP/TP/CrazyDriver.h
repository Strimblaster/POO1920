#ifndef CrazyDriver_H
#define CrazyDriver_H

#include "Piloto.h"
class CrazyDriver :public Piloto
{
	int tempoDesatento;
	int posicao_anterior;
public:
	CrazyDriver(string nome, vector<Piloto*> pilotos);
	int mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida) override;
	void reset() override;
	void resetTempoDesatento();
	void resetPosicao_anterior();
};

#endif
