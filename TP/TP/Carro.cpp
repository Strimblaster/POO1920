#include <string>
#include <iostream>
#include "Carro.h"

using namespace std;




Carro::Carro(string marca, string modelo, int capacidadeMax, int energiaInicial, int velocidadeMax):capacidadeMax(capacidadeMax), velocidadeMax(velocidadeMax) {
	this->marca = marca;
	this->modelo = modelo;
	if ('a' + this->contador > 'z')
		this->id = '?';
	else
		this->id = 'a' + this->contador++;
	this->velocidade = 0;
	this->estado = parado;
	this->energia = energiaInicial;
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


