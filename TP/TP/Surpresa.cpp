#include "Surpresa.h"
#include "Carro.h"
#include "Campeonato.h"

Surpresa::Surpresa(string nome, vector<Piloto*> pilotos) :Piloto(nome, pilotos, "Surpresa")
{

}

int Surpresa::mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida)
{
	//Stop
	if (getParar()) {
		ostringstream oss;
		oss << getNome() << " esta a parar (Comando STOP) " << endl;
		Campeonato::addLog(oss.str());
		return carro->travar();
	}

	if (finalDaCorrida) {
		if (posicao == nCarros) {
			ostringstream oss;
			oss << getNome() << " desistiu da corrida porque está em ultimo perto do final. " << endl;
			Campeonato::addLog(oss.str());
			carro->ativarSinalEmergencia();
			return carro->manterVelocidade();
		}
		else {
			return carro->acelerar(3);
		}
	}

		
	return carro->acelerar();
}


