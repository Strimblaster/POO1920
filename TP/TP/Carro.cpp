#include <string>
#include <iostream>
#include <sstream>
#include "Carro.h"

using namespace std;




Carro::Carro(string marca, string modelo, int capacidadeMax, int energiaInicial, int velocidadeMax):capacidadeMax(capacidadeMax), velocidadeMax(velocidadeMax) {
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

void Carro::mover() {
	if (estado == danificado || estado == parado || piloto == nullptr) return;
	if (energia == 0)
		travar();
	//else
		//mexer();

}

void Carro::entrarPiloto(Piloto* p) {
	if(estado != parado && piloto != nullptr && estado != danificado)
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

int Carro::contador = 0;


