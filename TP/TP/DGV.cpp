#include "DGV.h"
#include <iostream>

DGV::DGV() {
	pilotos.push_back(new Piloto("PA", pilotos));
	pilotos.push_back(new Piloto("PB", pilotos));
	pilotos.push_back(new Piloto("PC", pilotos));

	carros.push_back(new Carro("Mercedes", "Corno", 6000, 4000, 100));
	carros.push_back(new Carro("Mercedes", "Corno", 6000, 4000, 100));
	carros.push_back(new Carro("Mercedes", "Corno", 6000, 4000, 100));

	autodromos.push_back(new Autodromo("A1", 5, 100, autodromos));
	autodromos.push_back(new Autodromo("A2", 5, 100, autodromos));
	autodromos.push_back(new Autodromo("A3", 5, 100, autodromos));
	campeonato = nullptr;
	//carros.push_back(new Carro("Mercedes", "Corno", 6000, 4000, 100));
}

void DGV::cria(vector<string> comando) {
	if (comando.at(1) == "c") {
		if (comando.size() < 8) throw string("Usar: cria c capacidadeMax energiaInicial marca modelo velMax");
		try {
			addCarro(new Carro(comando.at(4), comando.at(5), stoi(comando.at(2)), stoi(comando.at(3)), stoi(comando.at(6))));
		}
		catch (invalid_argument ex) {
			throw string("Usar: cria c marca modelo capacidadeMax energiaInicial velMax");
		}
	}
	else if (comando.at(1) == "p") {
		if (comando.size() < 4) throw string("Usar: cria p nome");
		addPiloto(new Piloto(comando.at(2), pilotos));
	}
	else if (comando.at(1) == "a") {
		if (comando.size() < 4) throw string("Usar: cria a");
		
	}
	else
		throw string("Usar: cria <c,p,a>");

}

void DGV::entraNoCarro(vector<string> comando)
{
	if (comando.size() != 4 || comando.at(1).size() != 1) throw string("Usar: entranocarro IDCarro NomePiloto");
	Piloto* piloto = nullptr;

	//Verifica se o piloto existe
	for (Piloto* p : pilotos)
		if (p->getNome() == comando.at(2))
			piloto = p;
	if (piloto == nullptr) throw string("O piloto não existe");

	//Verifica se ja esta em algum carro
	for (Carro* c : carros) {
		if (c->getPiloto() == piloto)
			throw string("O piloto ja esta num carro");
	}

	//Procura o carro e mete la o piloto
	for (Carro* c : carros) {
		if (c->getid() == comando.at(1)[0]) {
			c->entrarPiloto(piloto);
		}
			
	}

}

void DGV::addAutodromo(Autodromo* a)
{
	autodromos.push_back(a);
}

void DGV::addCarro(Carro* c) {
	carros.push_back(c);
}

void DGV::addPiloto(Piloto* c) {
	pilotos.push_back(c);
}

string DGV::listaPilotos()
{
	ostringstream oss;
	oss << "----- Lista de Pilotos -----" << endl;
	if (pilotos.size() == 0) {
		oss << "Nao existem pilotos";
		return oss.str();
	}
	for (Piloto* p : pilotos)
		oss << "Piloto: " << p->toString() << endl;

	return oss.str();
}

string DGV::lista()
{
	ostringstream oss;
	oss << listaPilotos() << endl << listaCarros() << endl << listaAutodromos();
	return oss.str();
}

void DGV::saiDoCarro(vector<string> comando)
{
	if (comando.size() < 3) throw string("Usar: saidocarro IDCarro");
	if (comando.at(1).size() != 1) throw string("Usar: saidocarro IDCarro");
	for (Carro* c : carros)
		if (c->getid() == comando.at(1)[0])
			c->sairPiloto();
}


string DGV::listaCarros() {
	ostringstream s;

	if (carros.size() == 0)
		return "Nao existem carros\n";

	s << endl << " --- Lista de Carros ---" << endl;
	for (Carro* c : carros) {
		s << c->toString() << endl;
	}

	return s.str();
}

void DGV::comandoCampeonato(vector<string> comando) {
	if (comando.size() < 3) throw string("Usar: campeonato A1 A2 ... An");
	Autodromo* aut = nullptr;
	for (Autodromo* a : autodromos)
		if (a->getNome() == comando.at(1))
			aut = a;
	if (aut == nullptr)
		throw string("Autodromo nao encontrado");
	vector<Autodromo*> pistas;
	pistas.push_back(aut);
	this->campeonato = new Campeonato(pistas, pilotos, carros);
}

int DGV::getLargura()
{
	if (campeonato == nullptr)
		throw string("erro");
	campeonato->getLargura();
}

int DGV::getComprimento()
{
	if (campeonato == nullptr)
		throw string("erro");
	campeonato->getComprimento();
}

string DGV::listaAutodromos()
{
	ostringstream oss;
	oss << "--- Lista de Autodromos ---" << endl;
	for (Autodromo* a : autodromos) {
		oss << a->toString() << endl;
	}
	return oss.str();
}

void DGV::infoCampeonato()
{
	if (campeonato != nullptr)
		cout << campeonato->infoCampeonato();
}

void DGV::scoreboard()
{
	if (campeonato != nullptr)
		cout << campeonato->scoreboard();
}

string DGV::getGaragem()
{
	return campeonato->getGaragem();
}

map<Carro*, int> DGV::getPosicoes()
{
	return campeonato->getPosicoes();
}
