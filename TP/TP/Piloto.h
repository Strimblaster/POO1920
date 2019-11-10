
#ifndef Piloto_H
#define Piloto_H

#include <string>

using namespace std;
class Piloto
{
	string nome;


public:
	Piloto(string);

	string getNome() const;
};

#endif