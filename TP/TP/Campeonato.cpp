#include "Campeonato.h"

Campeonato::Campeonato(vector<Autodromo*> pistas, vector<Piloto*> pilotos, vector<Carro*> carros) {
	//Copia dos autodromos
	this->pistas = new vector<Autodromo*>(pistas);

	//Copia todos os carros que têm piloto e não estão danificados
	vector<Carro*> car;
	for (Carro* c : carros)
		if (c->estado == Carro::Estado::parado && c->getPiloto() != nullptr)
			car.push_back(c);

	if (car.size() < 2) throw string("Erro: Nao ha 2 carros com pilotos disponiveis para campeonato");
	this->carros = car;

	//Percorre todos os carros que foram inseridos antes e adiciona no Map todos os Pilotos que vao participar
	for (Carro* c : this->carros)
		this->pontuacao.insert(pair<Piloto*, int>(c->getPiloto(), 0));

	corridaAtual = 0;
	//Mete os carros no Autodromo da primeira corrida
	for (Carro* c : this->carros)
		this->pistas->at(corridaAtual)->autodromoController(c);
}

string Campeonato::scoreboard()
{
	ostringstream oss;
	oss << "---------- Scoreboard -----------" << endl;

	map<Piloto*, int> map = pontuacao;
	
	while (map.size() > 1) {
		pair<Piloto*, int> maior(nullptr, -1);
		for (pair<Piloto*, int> p : map) {
			if (p.second > maior.second)
				maior = p;
		}
		oss << "Piloto: " << maior.first->getNome() << " Pontuacao: " << maior.second << endl;
		map.erase(maior.first);
	}

	return oss.str();
}


string Campeonato::infoCampeonato()
{
	ostringstream oss;
	oss << endl << "---- InfoCampeonato ---" << endl;

	oss << "- Carros -" << endl;
	for (Carro* c : carros)
		oss << c->getid() << " " << c->getPiloto()->getNome() << endl;

	oss << "- Autodromos -" << endl;
	for (Autodromo* a : *pistas)
		oss << a->toString() << endl;
	return oss.str();
}

string Campeonato::getGaragem()
{
	return pistas->at(corridaAtual)->getGaragem();
}

map<Carro*, int> Campeonato::getPosicoes()
{
	return pistas->at(corridaAtual)->getPosicoes();
}

int Campeonato::getLargura()
{
	return pistas->at(corridaAtual)->getLargura();
}

int Campeonato::getComprimento()
{
	return pistas->at(corridaAtual)->getComprimento();
}

bool Campeonato::passaTempo()
{
	bool terminou = pistas->at(corridaAtual)->passaTempo();
	int k = 0;
	if (terminou)
		for (Piloto* p : pistas->at(corridaAtual)->getTop3())
			for (pair<Piloto*, int> par : pontuacao)
				if (p == par.first) {
					par.second += 10 / (k + 1);
					k++;
				}
	return terminou;
}
