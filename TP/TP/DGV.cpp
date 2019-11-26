#include "DGV.h"
#include <iostream>
#include <fstream>
#include <algorithm>

DGV::DGV() {
	campeonato = nullptr;
	//carros.push_back(new Carro("Mercedes", "Corno", 6000, 4000, 100));
	carros.push_back(new Carro("Mercedes", 6000, 4000, 1000));
	carros.push_back(new Carro("Mercedes", 6000, 4000, 300));
	carros.push_back(new Carro("Mercedes", 6000, 4000, 500));

	pilotos.push_back(new Piloto("P1", pilotos));
	pilotos.push_back(new Piloto("P2", pilotos));
	pilotos.push_back(new Piloto("P3", pilotos));

	autodromos.push_back(new Autodromo("A1", 5, 1000, autodromos));
	autodromos.push_back(new Autodromo("A1", 5, 1500, autodromos));
	autodromos.push_back(new Autodromo("A1", 5, 600, autodromos));
}

DGV::~DGV() {
	while (carros.size() != 0) {
		delete carros.at(0);
		carros.erase(carros.begin());
	}
	while (pilotos.size() != 0) {
		delete pilotos.at(0);
		pilotos.erase(pilotos.begin());
	}
	while (autodromos.size() != 0) {
		delete autodromos.at(0);
		autodromos.erase(autodromos.begin());
	}
	delete campeonato;
}


void DGV::cria(vector<string> comando) {
	if (comando.at(1) == "c") {
		if (comando.size() != 8 && comando.size() != 7) throw string("Usar: cria c capacidadeMax energiaInicial marca velMax modelo");
		if(comando.size() == 8)
			try {
				addCarro(new Carro(comando.at(4), stoi(comando.at(2)), stoi(comando.at(3)), stoi(comando.at(5)), comando.at(6)));
			}
			catch (invalid_argument ex) {
				throw string("Usar: cria c marca modelo capacidadeMax energiaInicial velMax");
			}
		if (comando.size() == 7)
			try {
				addCarro(new Carro(comando.at(4), stoi(comando.at(2)), stoi(comando.at(3)), stoi(comando.at(5))));

			}
			catch (invalid_argument ex) {
				throw string("Usar: cria c marca modelo capacidadeMax energiaInicial velMax");
			}
		cout << "Carro criado!" << endl;
	}
	else if (comando.at(1) == "p") {
		if (comando.size() < 4) throw string("Usar: cria p Nome");
		ostringstream oss;
		for (unsigned int i = 2; i < comando.size()-1; i++)
		{	
			if (i > 2)
				oss << " ";
			oss << comando.at(i);
		}
		addPiloto(new Piloto(oss.str(), pilotos));
		cout << "Piloto criado!" << endl;
	}
	else if (comando.at(1) == "a") {
		if (comando.size() != 6) throw string("Usar: cria a Nome nMaxCarros Comprimento");
		addAutodromo(comando);
		cout << "Autodromo criado!" << endl;
	}
	else
		throw string("Usar: cria <c,p,a>");

}

void DGV::apaga(vector<string> comando) {
	if (comando.at(1) == "c") {
		if (comando.size() != 4 ) throw string("Usar: apaga c IDCarro");
		Carro* car = nullptr;
		for (Carro* c : carros)
			if (c->getid() == comando.at(2)[0])
				car = c;
		if (car == nullptr) throw string("Carro nao encontrado");
		for (unsigned int i = 0; i < carros.size(); i++)
			if (carros.at(i) == car)
				carros.erase(carros.begin() + i);
		delete car;
	}
	else if (comando.at(1) == "p") {
		if (comando.size() < 4) throw string("Usar: apaga p Nome");
		Piloto* p = nullptr;
		ostringstream nome;
		for (unsigned int i = 2; i < comando.size() - 1; i++)
		{
			if (i > 2)
				nome << " ";
			nome << comando.at(i);
		}
		for (Piloto* i : pilotos)
			if (i->getNome() == nome.str())
				p = i;
		if (p == nullptr) throw string("Piloto nao encontrado");
		for (Carro* c : carros)
			if (c->getPiloto() == p)
				c->sairPiloto();

		for (unsigned int i = 0; i < pilotos.size(); i++) {
			if (pilotos.at(i) == p)
				pilotos.erase(pilotos.begin() + i);
		}
		delete p;
	}
	else if (comando.at(1) == "a") {
		if (comando.size() != 4) throw string("Usar: apaga a Nome");
		Autodromo* aut = nullptr;
		for (Autodromo* a : autodromos)
			if (a->getNome() == comando.at(2))
				aut = a;
		if (aut == nullptr) throw string("Autodromo nao encontrado");
		for (unsigned int i = 0; i < autodromos.size(); i++)
			if (autodromos.at(i) == aut)
				autodromos.erase(autodromos.begin() + i);
		delete aut;
	}
	else
		throw string("Usar: apaga <c,p,a>");
}

void DGV::carregaP(vector<string> comando)
{
	if (comando.size() != 3) throw string("Usar: carregaP NomeFicheiro");
	ifstream f(comando.at(1));
	if (!f.is_open()) throw string("Erro ao abrir o ficheiro");
	string line;
	while (getline(f, line))
	{
		istringstream iss(line);
		ostringstream nome;
		string tipo;
		iss >> tipo;
		for (int i = 0; iss; i++)
		{
			string temp;
			iss >> temp;
			if (i > 0) nome << " ";
			nome << temp;
		}
		
		string n = nome.str();
		if (tipo != "generico" || n.size() == 0) continue;
		n.erase(remove_if(n.end()-1, n.end(), isspace), n.end());

		addPiloto(new Piloto(n, pilotos));
	}
	f.close();

}

void DGV::carregaA(vector<string> comando)
{
	if (comando.size() != 3) throw string("Usar: carregaA NomeFicheiro");
	ifstream f(comando.at(1));
	if (!f.is_open()) throw string("Erro ao abrir o ficheiro");
	string line;
	while (getline(f, line))
	{
		istringstream iss(line);
		string nCarros, comprimento,nome;
		iss >> nCarros;
		iss >> comprimento;
		iss >> nome;
		if (comprimento.size() == 0 || nCarros.size() == 0 || nome.size() == 0) continue;
		try {
			autodromos.push_back(new Autodromo(nome, stoi(nCarros), stoi(comprimento), autodromos));
		}
		catch (invalid_argument ex) {
			continue;
		}
	}
	f.close();

}

void DGV::carregaC(vector<string> comando)
{
	if (comando.size() != 3) throw string("Usar: carregaC NomeFicheiro");
	ifstream f(comando.at(1));
	if (!f.is_open()) throw string("Erro ao abrir o ficheiro");
	string line;
	while (getline(f, line))
	{
		istringstream iss(line);
		string velMax, capInicial, capMaxima, marca, modelo;
		iss >> velMax;
		iss >> capInicial;
		iss >> capMaxima;
		iss >> marca;
		iss >> modelo;
		if (velMax.size() == 0 || capInicial.size() == 0 || capMaxima.size() == 0 || marca.size() == 0) continue;
		try {
			if (modelo.size() == 0) {
				addCarro(new Carro(marca, stoi(capMaxima), stoi(capInicial), stoi(velMax)));
			}
			else {
				addCarro(new Carro(marca, stoi(capMaxima), stoi(capInicial), stoi(velMax), modelo));
			}
		}
		catch (invalid_argument ex) {
			continue;
		}
	}
	f.close();

}

void DGV::entraNoCarro(vector<string> comando)
{
	if (comando.size() < 4 || comando.at(1).size() != 1) throw string("Usar: entranocarro IDCarro NomePiloto");
	Piloto* piloto = nullptr;
	ostringstream nome;
	for (unsigned int i = 2; i < comando.size() - 1; i++)
	{
		if (i > 2)
			nome << " ";
		nome << comando.at(i);
	}
	//Verifica se o piloto existe
	for (Piloto* p : pilotos)
		if (p->getNome() == nome.str())
			piloto = p;
	if (piloto == nullptr) throw string("O piloto nao existe");

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

void DGV::addAutodromo(vector<string> comando)
{
	autodromos.push_back(new Autodromo(comando.at(2), stoi(comando.at(3)), stoi(comando.at(4)), autodromos));
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
	s << endl << " --- Lista de Carros ---" << endl;
	if (carros.size() == 0)
		s << "Nao existem carros\n";
	for (Carro* c : carros) {
		s << c->toString();
	}

	return s.str();
}

void DGV::comandoCampeonato(vector<string> comando) {
	if (comando.size() < 3) throw string("Usar: campeonato A1 A2 ... An");
	Autodromo* aut = nullptr;
	vector<Autodromo*> pistas;
	for (unsigned int i = 1; i < comando.size()-1; i++)
	{
		for (Autodromo* a : autodromos)
			if (a->getNome() == comando.at(i))
				aut = a;
		if (aut == nullptr)
			continue;
		pistas.push_back(aut);
	}
	if (pistas.size() == 0) throw string("Nenhum autodromo encontrado");
	this->campeonato = new Campeonato(pistas, pilotos, carros);
}

int DGV::getLargura()
{
	if (campeonato == nullptr)
		throw string("erro");
	return campeonato->getLargura();
}

int DGV::getComprimento()
{
	if (campeonato == nullptr)
		throw string("erro");
	return campeonato->getComprimento();
}

string DGV::listaAutodromos()
{
	ostringstream oss;
	oss << "--- Lista de Autodromos ---" << endl;
	if (autodromos.size() == 0)
		oss << "Nao existem autodromos" << endl;

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

bool DGV::passaTempo()
{

	return campeonato->passaTempo();
}

bool DGV::corridaADecorrer()
{
	if (campeonato == nullptr)
		return false;
	return campeonato->partidaADecorrer();
}

bool DGV::proxCorrida()
{
	if (campeonato->proximaCorrida()) {
		for (Autodromo* a : autodromos)
			a->clear();
		delete campeonato;
		campeonato = nullptr;
		return true;
	}
	else 
		return false;
}

string DGV::listaCarrosCampeonato()
{
	return campeonato->listaCarros();
}

