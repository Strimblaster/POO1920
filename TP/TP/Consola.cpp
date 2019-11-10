#include "Consola.h"
#include "ConsolaUtils.h"


Consola::Consola(DGV* j) {
	this->dgv = j;
}

void Consola::start() {
	while (nextCommand());
}

bool Consola::nextCommand() {
	
	while (true) {
		string c;
		getline(cin, c);

		istringstream iss(c);
		vector<string> comando;
		while (iss) {
			string temp;
			iss >> temp;
			comando.push_back(temp);

		}

		try {
			if (comando.at(0) == "listacarros") {
				cout << dgv->listaCarros();
			}
			else if (comando.at(0) == "cria")
				dgv->cria(comando);
		}
		catch (string ex) {
			cout << ex << endl;
		}

	}
	
	return false;
}
