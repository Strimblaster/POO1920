#include "Carro.h"
#include "Via.h"
#include <vector>
#include <map>
#include <sstream>

#ifndef Autodromo_H
#define Autodromo_H
using namespace std;
class Autodromo
{
	vector<Carro*> garagem;
	vector<Via*> pista;
	const int largura;
	const int comprimento;
	string nome;

public:
	Autodromo(string, int, int, vector<Autodromo*>);
	string getNome();
	int getLargura();
	int getComprimento();
	string toString();
	void autodromoController(Carro*);
	string getGaragem();
	vector<Via*> getPosicoes();
	bool passaTempo();
	bool gameEnded();
	vector<Piloto*> getTop3();
	string listaCarros();
	vector<Carro*> getGaragem(int i);
	void clear();
	void sortVias();
	void destroiCarro(char);

};
#endif
