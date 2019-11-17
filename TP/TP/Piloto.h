
#ifndef Piloto_H
#define Piloto_H

#include <string>
#include <vector>

using namespace std;
class Piloto
{
	string nome;


public:
	Piloto(string, vector<Piloto*>);

	string getNome() const;
	string toString();
};

#endif