#include <string>
#include <iostream>
#include <sstream>
#include "Carro.h"

using namespace std;




Carro::Carro(string marca, int capacidadeMax, int energiaInicial, int velocidadeMax, string modelo):capacidadeMax(capacidadeMax), velocidadeMax(velocidadeMax) {
	if (energiaInicial > capacidadeMax) throw string("A Energia Inicial do carro deve ser inferior à Capacidade Maxima");
	this->marca = marca;
	this->modelo = modelo;
	if ('A' + this->contador > 'Z')
		this->id = '?';
	else
		this->id = 'A' + this->contador++;
	this->velocidade = 0;
	this->estado = parado;
	this->energia = (float)energiaInicial;
	sinalEmergencia = false;
}

void Carro::acelerar() {
	if (estado == danificado || piloto == nullptr) return;
	if (energia > 0 && velocidade < velocidadeMax)
		velocidade++;
}

void Carro::travar() {
	if (estado == danificado || piloto == nullptr) return;
	velocidade--;
}

int Carro::mover() {
	//if (estado == danificado || estado == parado || piloto == nullptr) return 0;
	if (energia == 0)
		travar();
	else
		acelerar();

	return velocidade;
}

void Carro::entrarPiloto(Piloto* p) {
	if (estado != parado) throw string("Erro: O carro tem que estar parado");
	if(piloto != nullptr) throw string("Erro: O carro ja tem um condutor");
	if(estado == danificado) throw string("Erro: O carro esta danificado");
	piloto = p;
}

string Carro::toString() {
	ostringstream o;

	o << "ID: " << id;
	if (piloto != nullptr)
		o << " Piloto: " << piloto->getNome();
	o << " Marca: " << marca << " Modelo: " << modelo << " Capacidade Maxima:" << capacidadeMax << endl;

	return o.str();
}


void Carro::sairPiloto()
{
	if (estado == movimento)
		throw string("O carro esta em movimento");
	piloto = nullptr;
}




const char Carro::getid()
{
	return id;
}

int Carro::contador = 0;

Piloto* Carro::getPiloto() {
	return piloto;
}


