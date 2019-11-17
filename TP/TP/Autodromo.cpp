#include "Autodromo.h"


Autodromo::Autodromo(string nome, int largura, int comprimento, vector<Autodromo*> autodromos):comprimento(comprimento),largura(largura) {
	for (int i = 0; i < autodromos.size(); i++)
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
	if (carro->estado == Carro::danificado || carro->getPiloto() == nullptr) throw string("Erro: Este carro n�o pode correr\n");
	
	//Se o carro estiver na garagem, mete na pista
	for (int i = 0; i < garagem.size(); i++)
		if (carro == garagem.at(i)) {
			//Falta verificar se tem espa�o na pista
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

	//Chegando aqui, o carro n�o est� no Autodromo
	//Adiciona o carro na pista se couber (se n�o na garagem)

	if (posicoes.size() < largura)
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

map<Carro*, int> Autodromo::getPosicoes()
{
	return posicoes;
}