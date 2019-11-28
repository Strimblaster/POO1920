#include "CrazyDriver.h"

CrazyDriver::CrazyDriver(string nome, vector<Piloto*> pilotos):Piloto(nome, pilotos)
{
	tipo = "Crazy";
	tempoDesatento = rand() % 5 + 1;
}

int CrazyDriver::mover(float energia, int capacidadeMax, int posicao) {

	if (energia == 0) return 0;
	return 2;
}
