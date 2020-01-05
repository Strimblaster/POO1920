#include "Autodromo.h"
#include "Piloto.h"
#include <algorithm>


Autodromo::Autodromo(string nome, int largura, int comprimento, vector<Autodromo*> autodromos):comprimento(comprimento),largura(largura) {
	for (unsigned int i = 0; i < autodromos.size(); i++)
		if (autodromos.at(i)->getNome() == nome) {
			nome += "1";
			i = -1;
	}

	this->nome = nome;
}


string Autodromo::getNome()
{
	return nome;
}

int Autodromo::getLargura()
{
	return largura;
}

int Autodromo::getComprimento()
{
	return comprimento;
}

string Autodromo::toString()
{
	ostringstream oss;

	oss << "Nome: " << nome << " MaxVeiculos: " << largura << " Comprimento: " << comprimento;
	if (garagem.size() != 0)
		oss << " Garagem: ";
	for (Carro* c : garagem)
		oss << c->getid() << " ";

	return oss.str();
}

void Autodromo::autodromoController(Carro* carro)
{

	
	//Se o carro estiver na garagem, mete na pista
	if (!(carro->estado == Carro::danificado || carro->getPiloto() == nullptr))
		for (auto i = 0; i < garagem.size(); i++)
			if (carro == garagem.at(i)) {
				//Falta verificar se tem espaço na pista
				pista.push_back(new Via(carro, static_cast<int>(pista.size()), comprimento));
				garagem.erase(garagem.begin()+i);
				return;
			}
	//Se o carro estiver na pista, mete na garagem
	for(auto it=pista.begin(); it != pista.end(); it++)
		if ((*it)->getCarro() == carro) {
			garagem.push_back((*it)->getCarro());
			pista.erase(it);
			return;
		}

	//Chegando aqui, o carro não está no Autodromo
	//Adiciona o carro na pista se couber (se não na garagem)
	if(carro->estado == Carro::danificado || carro->getPiloto() == nullptr)
		garagem.push_back(carro);
	else if (pista.size() < static_cast<int>(largura))
		pista.push_back(new Via(carro, static_cast<int>(pista.size()), comprimento));
	else
		garagem.push_back(carro);

}

string Autodromo::getGaragem()
{
	ostringstream oss;
	for (Carro* c : garagem){
		if (c->getPiloto() == nullptr)
			oss << (char)tolower(c->getid());
		else
			oss << c->getid();
		oss << " ";
	}
	return oss.str();
}

vector<Carro*> Autodromo::getGaragem(int i) {
	return garagem;
}

void Autodromo::clear()
{
	garagem.clear();
	pista.clear();
}

vector<Via*> Autodromo::getPosicoes()
{
	return pista;
}

bool Autodromo::passaTempo()
{
	sortVias();
	for (auto i = 0; i < pista.size(); i++) {
		if (pista.at(i)->getPosicao() < comprimento)
			pista.at(i)->mover(comprimento, i + 1, static_cast<int>(pista.size()));
		if (pista.at(i)->getCarro()->getSinalEmergencia() || pista.at(i)->getCarro()->estado == Carro::Estado::danificado)
			autodromoController(pista.at(i)->getCarro());
		else if(pista.at(i)->getCarro()->getPiloto() != nullptr)
			if(pista.at(i)->getCarro()->getPiloto()->getParar() && pista.at(i)->getCarro()->getVelocidade() == 0)
				autodromoController(pista.at(i)->getCarro());


	}

	if (gameEnded()) return true;
	return false;
}

bool Autodromo::gameEnded()
{
	int i = 0;
	for (Via* p : pista)
		if (p->getPosicao() >= comprimento)
			i++;
	return i == pista.size();
}

vector<Piloto*> Autodromo::getTop3()
{
	sortVias();
	vector<Piloto*> p;
	for (unsigned int i = 0; i < 3 && i < pista.size(); i++)
		p.push_back(pista.at(i)->getCarro()->getPiloto());
	return p;
}

string Autodromo::listaCarros() {
	ostringstream oss;
	oss << "---- Lista de Carros na Pista ----" << endl << endl;
	sortVias();
	int i = 1;
	for (auto it = pista.begin(); it != pista.end(); it++) {
		oss << i << " - " << (*it)->getPosicao() << "m : " << (*it)->getCarro()->toStringBoard() << endl;
		i++;
	}

	return oss.str();
}

bool comparador(Via* i, Via* j) {
	if (i->getPosicao() > j->getPosicao())
		return true;
	else if (i->getPosicao() == j->getPosicao()) {
		return i->getTempo() < j->getTempo();
	}
	return (i->getPosicao() > j->getPosicao()); 
}

void Autodromo::sortVias() {
	
	sort(pista.begin(), pista.end(), comparador);
}

void Autodromo::destroiCarro(char letraCarro)
{
	for (auto i = 0; i < pista.size(); i++) {
		if (pista.at(i)->getCarro()->getid() == letraCarro) {
			pista.erase(pista.begin() + i);
		}
	}
}

