#include <string>
#include <iostream>
#include <sstream>
#include "Carro.h"
#include "Piloto.h"

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
	this->energia = (float)energiaInicial;
	sinalEmergencia = false;
	estado = parado;
}
int Carro::acelerar(int n) {
	if (estado == danificado || piloto == nullptr) throw string("O carro não tem piloto ou está danificado");
	if (energia <= 0) {
		if(velocidade > 0)
			velocidade--;
		if (velocidade == 0)
			estado = parado;
		return velocidade;
	}
	
	estado = movimento;
	velocidade += n;
	if (velocidade > velocidadeMax)
		velocidade = velocidadeMax;

	gastaEnergia();
	return velocidade;
}

int Carro::travar() {
	if (estado == danificado || piloto == nullptr) throw string("O carro não tem piloto ou está danificado");
	if (energia <= 0 && velocidade > 0) 
		velocidade--;
	if (velocidade > 0)
		velocidade--;
	if (velocidade == 0) estado = parado;

	gastaEnergia();
	return velocidade;
}

int Carro::manterVelocidade()
{
	if (energia == 0)
		velocidade--;
	else
		gastaEnergia();
	return velocidade;
}

void Carro::gastaEnergia()
{
	energia = energia - (float)(0.1 * velocidade);
	if (energia < 0)
		energia = 0;
}

void Carro::ativarSinalEmergencia()
{
	sinalEmergencia = true;
}

void Carro::reset()
{
	sinalEmergencia = false;
	if (piloto != nullptr)
		piloto->reset();
}

int Carro::getVelocidade()
{
	return velocidade;
}



float Carro::getEnergia()
{
	return energia;
}

bool Carro::getSinalEmergencia()
{
	return sinalEmergencia;
}

int Carro::getEnergiaMax()
{
	return capacidadeMax;
}


void Carro::entrarPiloto(Piloto* p) {
	if (estado != parado) throw string("Erro: O carro tem que estar parado");
	if(piloto != nullptr) throw string("Erro: O carro ja tem um condutor");
	if(estado == danificado) throw string("Erro: O carro esta danificado");
	piloto = p;
}

string Carro::toString() {
	ostringstream o;

	if (piloto != nullptr)
		o << "ID: " << id << " Piloto: " << piloto->getNome();
	else {
		char idlower = tolower(id);
		o << "ID: " << idlower;
	}
	o << " Marca: " << marca << " Modelo: " << modelo << " EnergiaMaxima:" << capacidadeMax << " VelMax:" << velocidadeMax;
	if (estado == danificado)
		o << " DANIFICADO";
	o << endl;

	return o.str();
}

string Carro::toStringBoard() {
	ostringstream o;

	o << "ID: " << id;
	if (piloto != nullptr)
		o << " Piloto: " << piloto->toString();
	else {
		char idlower = tolower(id);
		o << "ID: " << idlower;
	}
	o << " Estado: ";
	if (estado == parado)
		o << "parado";
	else if (estado == movimento)
		o << "movimento";
	else if (estado == danificado)
		o << "danificado";
	o << " Energia:" << energia << " Velocidade:" << velocidade << " VelMax:" << velocidadeMax  << endl;

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

void Carro::setVel(int v) {
	velocidade = v;
	if (v == 0) estado = parado;
	else estado = movimento;
}

void Carro::carrega(int n)
{
	if (estado == danificado) throw string("O carro está danificado!");
	if (estado == movimento) throw string("O carro não está parado!");
	energia += n;
	if (energia > capacidadeMax)
		energia = (float)capacidadeMax;
}

void Carro::carregaTudo() {
	if (estado == danificado) return;
	if (estado == movimento) return;
	energia = (float)capacidadeMax;
}

void Carro::danificar()
{
	estado = danificado;
	velocidade = 0;
	piloto = nullptr;
}




