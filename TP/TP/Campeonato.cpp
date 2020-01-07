#include "Piloto.h"
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

	corridaAtual = -1;
	corridaAnterior = -1;
	//Mete os carros no Autodromo da primeira corrida
	for (Carro* c : this->carros) {
		this->pistas->at(0)->autodromoController(c);
		c->reset();
	}
}

Campeonato::~Campeonato() {
	delete pistas;
}

string Campeonato::scoreboard()
{
	ostringstream oss;
	oss << "---------- Scoreboard -----------" << endl;

	map<Piloto*, int> map = pontuacao;
	
	while (map.size() > 0) {
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

bool Campeonato::proximaCorrida()
{
	if (!partidaADecorrer()) {
		corridaAtual = corridaAnterior + 1;
		if (corridaAtual == pistas->size())
			return true;
		if (corridaAtual != 0)
			moveCarros(pistas->at(corridaAnterior), pistas->at(corridaAtual));
	}
	else
		throw string("Partida já a decorrer");
	return false;
}

void Campeonato::moveCarros(Autodromo* anterior, Autodromo* atual)
{
	for (Via* p : anterior->getPosicoes())
	{
		atual->autodromoController(p->getCarro());
		p->getCarro()->reset();
	}

	for (Carro* carro : anterior->getGaragem(0))
	{
		atual->autodromoController(carro);
		carro->reset();
	}

}


string Campeonato::infoCampeonato()
{
	ostringstream oss;
	oss << endl << "---- InfoCampeonato ---" << endl << endl;

	oss << "- Carros -" << endl;
	for (Carro* c : carros)
		oss << c->toString();

	oss << "- Autodromos -" << endl;
	for (Autodromo* a : *pistas)
		oss << a->toString() << endl;


	return oss.str();
}

string Campeonato::getGaragem()
{
	return pistas->at(corridaAtual)->getGaragem();
}

vector<Via*> Campeonato::getPosicoes()
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
	if (terminou) {
		//Acrescenta a pontuação aos que ganharam
		for (Piloto* p : pistas->at(corridaAtual)->getTop3())
			for (pair<Piloto*, int> par : pontuacao)
				if (p == par.first) {
					pontuacao[p] += 10 / (k + 1);
					k++;
				}
		//Pára os carros
		for (Via* p : pistas->at(corridaAtual)->getPosicoes()) {
			p->getCarro()->setVel(0);
		}

		corridaAnterior = corridaAtual;
		corridaAtual = -1;
	}
	return terminou;
}

bool Campeonato::partidaADecorrer()
{
	return corridaAtual == -1 ? false : true;
}

string Campeonato::listaCarros()
{
	if (corridaAtual != -1) return pistas->at(corridaAtual)->listaCarros();
	if (corridaAnterior != -1) return pistas->at(corridaAnterior)->listaCarros();
	throw string("Nenhuma corrida inciada.");
}

void Campeonato::destroiCarro(char letraCarro)
{
	for(Autodromo* autodromo: *pistas)
	{
		autodromo->destroiCarro(letraCarro);
	}
	for (auto i = 0; (unsigned int)i < carros.size(); i++) {
		if (carros.at(i)->getid() == letraCarro)
			carros.erase(carros.begin() + i);
	}
}

void Campeonato::acidente(char letraCarro)
{
	Carro* c = nullptr;
	for (Carro* carro : carros) {
		if (carro->getid() == letraCarro) {
			carro->danificar();
			c = carro;
		}
	}
	if (c == nullptr)
		return;
	if (corridaAtual != -1)
		pistas->at(corridaAtual)->autodromoController(c);

}

vector<string> Campeonato::log;

void Campeonato::addLog(string s)
{
	log.push_back(s);
}

vector<string> Campeonato::getLog()
{
	return Campeonato::log;
}

