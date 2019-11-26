#include "Autodromo.h"


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
		for (unsigned int i = 0; i < garagem.size(); i++)
			if (carro == garagem.at(i)) {
				//Falta verificar se tem espaço na pista
				posicoes.insert(pair<Carro*, int>(garagem.at(i), 0));
				garagem.erase(garagem.begin()+i);
				return;
			}
	//Se o carro estiver na pista, mete na garagem
	for(pair<Carro*, int> p : posicoes)
		if (p.first == carro) {
			garagem.push_back(p.first);
			posicoes.erase(p.first);
			return;
		}

	//Chegando aqui, o carro não está no Autodromo
	//Adiciona o carro na pista se couber (se não na garagem)
	if(carro->estado == Carro::danificado || carro->getPiloto() == nullptr)
		garagem.push_back(carro);
	if (posicoes.size() < (unsigned)largura)
		posicoes.insert(pair<Carro*, int>(carro, 0));
	else
		garagem.push_back(carro);

}

string Autodromo::getGaragem()
{
	ostringstream oss;
	for (Carro* c : garagem)
		oss << c->getid() << " ";
	return oss.str();
}

vector<Carro*> Autodromo::getGaragem(int i) {
	return garagem;
}

void Autodromo::clear()
{
	garagem.clear();
	posicoes.clear();
}

map<Carro*, int> Autodromo::getPosicoes()
{
	return posicoes;
}

bool Autodromo::passaTempo()
{
	for (pair<Carro*, int> p : posicoes) {
		int i = p.first->mover();
		posicoes[p.first] += i;
		if(posicoes[p.first] > comprimento)
			posicoes[p.first] += comprimento;
	}
	if (gameEnded()) return true;
	return false;
}

bool Autodromo::gameEnded()
{
	for (pair<Carro*, int> p : posicoes)
		if (p.second >= comprimento)
			return true;
	return false;
}

vector<Piloto*> Autodromo::getTop3()
{
	vector<Piloto*> p;
	map<Carro*, int> cpy = posicoes;
	pair<Carro*, int> maior(nullptr, -1);
	for (int i = 0; i < 3; i++) {
		for (pair<Carro*, int> p : cpy)
			if (maior.second < p.second)
				maior = p;
		if (maior.first == nullptr) return p;
		p.push_back(maior.first->getPiloto());
		cpy.erase(maior.first);
		maior = pair<Carro*, int>(nullptr, -1);
	}
	return p;
}

string Autodromo::listaCarros() {
	ostringstream oss;
	oss << "---- Lista de Carros na Pista ----" << endl << endl;
	
	map<Carro*, int> cpy = posicoes;
	pair<Carro*, int> maior(nullptr, -1);
	for (int i = 0; cpy.size() != 0; i++) {
		for (pair<Carro*, int> p : cpy)
			if (maior.second < p.second)
				maior = p;
		oss << i + 1 << " - " << maior.second << "m : "<< maior.first->getid() << " Piloto: " << maior.first->getPiloto()->getNome() << endl ;
		cpy.erase(maior.first);
		maior = pair<Carro*, int>(nullptr, -1);
	}
	return oss.str();
}