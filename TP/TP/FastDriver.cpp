#include "FastDriver.h"
#include "Carro.h"
#include <sstream>
#include "Campeonato.h"

FastDriver::FastDriver(string nome, vector<Piloto*> pilotos) :Piloto(nome, pilotos, "FastDriver")
{
	contadorEnergia = 0;
	contadorAnsiedade = 0;
}

int FastDriver::mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida) {

	//Comando Stop
	if (getParar()) {
		ostringstream oss;
		oss << getNome() << " esta a parar (Comando STOP) " << endl;
		Campeonato::addLog(oss.str());
		return carro->travar();
	}

	//A cada 10s tem a probabilidade de ter um ataque de panico
	if (contadorAnsiedade == 10) {
		int r = rand() % 100 + 1;
		if (r < 5) {
			ostringstream oss;
			oss << getNome() << " teve um ataque de panico e ativou o sinal de emergencia" << endl;
			Campeonato::addLog(oss.str());
			carro->ativarSinalEmergencia();
			return carro->manterVelocidade();
		}
		contadorAnsiedade = 0;
	}
	else {
		contadorAnsiedade++;
	}

	//A metade da energia do carro acelera de 3 em 3 segundos
	if (carro->getEnergia() <= carro->getEnergiaMax() / 2) {
		if (contadorEnergia == 3) {
			ostringstream oss;
			oss << getNome() << " esta com menos de metade da energia (acelerar de 3 em 3s) " << endl;
			Campeonato::addLog(oss.str());
			contadorEnergia = 0;
			return carro->acelerar();
		}
		contadorEnergia++;
		return carro->manterVelocidade();
	}


	return carro->acelerar();
}

void FastDriver::reset()
{
	Piloto::reset();
	contadorEnergia = 0;
	contadorAnsiedade = 0;
}

