#include "FastDriver.h"

FastDriver::FastDriver(string nome, vector<Piloto*> pilotos) :Piloto(nome, pilotos)
{
	tipo = "Fast";
}

int FastDriver::mover(float energia, int capacidadeMax, int posicao) {

	if (energia == 0) return 0;
	return 3;
}

