#include "Autodromo.h"


Autodromo::Autodromo(string nome, int largura, int comprimento):comprimento(comprimento),largura(largura) {
	this->nome = nome;
}


string Autodromo::getNome()
{
	return nome;
}