#ifndef FastDriver_H
#define FastDriver_H

#include "Piloto.h"
class FastDriver : public Piloto
{

public:
	FastDriver(string, vector<Piloto*>);
	int mover(float energia, int capacidadeMax, int posicao) override;

};

#endif