#ifndef CrazyDriver_H
#define CrazyDriver_H

#include "Piloto.h"
class CrazyDriver :public Piloto
{
	int tempoDesatento;
	int posicao;
public:
	CrazyDriver(string nome, vector<Piloto*> pilotos);
	int mover(float energia, int capacidadeMax, int posicao) override;
};

#endif
