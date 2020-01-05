#include "CrazyDriver.h"
#include "Carro.h"
#include "Campeonato.h"

CrazyDriver::CrazyDriver(string nome, vector<Piloto*> pilotos):Piloto(nome, pilotos, "Crazy")
{
	tempoDesatento = rand() % 5 + 1;
	posicao_anterior = -1;
}

int CrazyDriver::mover(Carro* carro, int posicao, int nCarros, bool finalDaCorrida) {

	//Stop
	if (getParar()) {
		ostringstream oss;
		oss << getNome() << " esta a parar (Comando STOP) " << endl;
		Campeonato::addLog(oss.str());
		return carro->travar();
	}

	//Só começa a correr depois de X segundos
	if (tempoDesatento != 0) {
		tempoDesatento--;
		return 0;
	}

	//Se ficar sem energia, emergencia
	if (carro->getEnergia() == 0) {
		ostringstream oss;
		oss << getNome() << " fiquei sem energia e ativei o sinal de emergencia" << endl;
		Campeonato::addLog(oss.str());
		carro->ativarSinalEmergencia();
		return carro->manterVelocidade();
	}

	//Se tiver em 1º lugar mantém velocidade
	if (posicao == 1) return carro->manterVelocidade();

	//Se perder lugares acelera 2
	if (posicao_anterior == -1)
		posicao_anterior = posicao;
	else if (posicao < posicao_anterior) {
		ostringstream oss;
		oss << getNome() << " perdeu lugares e acelerou +2m/s" << endl;
		Campeonato::addLog(oss.str());
		posicao_anterior = posicao;
		return carro->acelerar(2);
	}
		
	
	return carro->acelerar();
}

void CrazyDriver::reset()
{
	Piloto::reset();
	resetPosicao_anterior();
	resetTempoDesatento();
}

void CrazyDriver::resetTempoDesatento()
{
	tempoDesatento = rand() % 5 + 1;
}

void CrazyDriver::resetPosicao_anterior()
{
	posicao_anterior = -1;
}
