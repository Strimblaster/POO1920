#include "Campeonato.h"

Campeonato::Campeonato(vector<Autodromo*> pistas, vector<Piloto*> pilotos, vector<Carro*> carros) {
	this->pistas = new vector<Autodromo*>(pistas);
	for (Piloto* p : pilotos) {
		this->pontuacao.insert(pair<Piloto*, int>(p, 0));
	}

	vector<Carro*> car;
	for (Carro* c : carros)
		if (c->estado == Carro::Estado::parado && c->getPiloto() != nullptr)
			car.push_back(c);

	if (car.size() < 2) throw string("Erro: Nao ha carros com pilotos disponiveis ");
	this->carros = car;
}

string Campeonato::scoreboard()
{
	ostringstream oss;
	oss << "---------- Scoreboard -----------" << endl;

	map<Piloto*, int> map = pontuacao;
	
	while (pontuacao.size() > 1) {
		pair<Piloto*, int> maior(nullptr, -1);
		for (pair<Piloto*, int> p : map) {
			if (p.second > maior.second)
				maior = p;
		}
		oss << "Piloto: " << maior.first->getNome() << " Pontuação: " << maior.second << endl;
		map.erase(maior.first);
	}

	return oss.str();
}
