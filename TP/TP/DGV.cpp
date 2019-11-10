#include "DGV.h"

DGV::DGV() {

}

void DGV::cria(vector<string> comando) {
	if (comando.at(1) == "c") {
		if (comando.size() < 8) throw string("Usar: cria c capacidadeMax energiaInicial marca modelo velMax");
		try {
			Carro c(comando.at(4), comando.at(5), stoi(comando.at(2)), stoi(comando.at(3)), stoi(comando.at(6)));
			addCarro(c);
		}
		catch (invalid_argument ex) {
			throw string("Usar: cria c marca modelo capacidadeMax energiaInicial velMax");
		}
	}
	else if (comando.at(1) == "p") {
		if (comando.size() < 4) throw string("Usar: cria p nome");
		Piloto p(comando.at(2));
		addPiloto(p);
	}

}

void DGV::addCarro(Carro c) {
	carros.push_back(c);
}

void DGV::addPiloto(Piloto c) {
	pilotos.push_back(c);
}

string DGV::listaCarros() {
	ostringstream s;

	if (carros.size() == 0)
		return "Nao existem carros\n";

	s << endl << " --- Lista de Carros ---" << endl;
	for (Carro c : carros) {
		s << c.toString() << endl;
	}

	return s.str();
}