#include "CrazyDriver.h"

CrazyDriver::CrazyDriver(string nome, vector<Piloto*> pilotos):Piloto(nome, pilotos)
{
	tipo = "Crazy";
	tempoDesatento = rand() % 5 + 1;
}

int CrazyDriver::mover(float energia, int capacidadeMax, int posicao, int nCarros) {

	if (energia == 0) return 0;

	//Só começa a correr depois de X segundos
	if (tempoDesatento != 0) {
		tempoDesatento--;
		return 0;
	}
	//Se tiver em 1º lugar mantém velocidade
	if (posicao == 1) return 0;

	//Se tiver em ultimo lugar trava
	if (posicao == nCarros) return -1;

	return 1;
}
