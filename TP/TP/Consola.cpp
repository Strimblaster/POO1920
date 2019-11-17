#include "Consola.h"
#include "ConsolaUtils.h"


Consola::Consola(DGV* j) {
	this->dgv = j;
	modo = 1;
}

void Consola::start() {
	ConsolaUtils::setBackgroundColor(ConsolaUtils::BRANCO);
	ConsolaUtils::setTextColor(ConsolaUtils::PRETO);
	ConsolaUtils::clrscr();
	ConsolaUtils::gotoxy(0, 25);
	while (nextCommand());
}

void Consola::desenharPista(int comprimento, int largura) {
	int xlinha1 = 7;
	int xlinha2 = xlinha1 + (comprimento * 10);
	int ylinha1 = 4;
	int ylinha2 = ylinha1 + (largura + 1);
	ConsolaUtils::clrscr();
	ConsolaUtils::gotoxy(xlinha1-3, ylinha1-2);
	cout << "Partida";
	ConsolaUtils::gotoxy(xlinha1 - 3 + comprimento, ylinha1 - 2);

	cout << "Chegada";
	
	ConsolaUtils::gotoxy(xlinha1-1, ylinha1);
	ostringstream oss;
	ConsolaUtils::setTextColor(ConsolaUtils::CINZENTO);
	for (int i = 0; i < comprimento+2; i++)
	{
		oss << '\xDB';
	}
	cout << oss.str();
	ConsolaUtils::gotoxy(xlinha1-1, ylinha2);
	cout << oss.str();
	ConsolaUtils::setTextColor(ConsolaUtils::PRETO);
	
	for (int i = ylinha1+1 ; i < ylinha2; i++)
	{
		ConsolaUtils::gotoxy(xlinha1 + comprimento, i );
		if( i%2 == 0)ConsolaUtils::setTextColor(ConsolaUtils::AZUL);
		else ConsolaUtils::setTextColor(ConsolaUtils::VERMELHO);
		cout << '\xBA';
	}
	ConsolaUtils::setTextColor(ConsolaUtils::PRETO);
	for (int i = ylinha1 + 1, j = 0; i < ylinha2; i++,j++)
	{
		ConsolaUtils::gotoxy(xlinha1-1, i);
		cout << '|';
	}

	map<Carro*, int> posicoes = dgv->getPosicoes();
	int k = 0;
	for (pair<Carro*, int> p : posicoes) {

		ConsolaUtils::gotoxy(xlinha1 - 1 + p.second, ylinha1 + 1 + k);
		cout << p.first->getid();
		k++;
	}


	ConsolaUtils::gotoxy(xlinha1-2, ylinha2 + 3);
	cout << "Garagem: " << dgv->getGaragem();
	



	/*ConsolaUtils::drawLine(xlinha1-20, ylinha1, xlinha2+20, ylinha1, RGB(0, 0, 0));
	ConsolaUtils::drawLine(xlinha1-20, ylinha2, xlinha2+20, ylinha2, RGB(0, 0, 0));

	ConsolaUtils::drawLine(xlinha1, ylinha1, xlinha1, ylinha2, RGB(0, 0, 255));
	ConsolaUtils::drawLine(xlinha2, ylinha1, xlinha2, ylinha2, RGB(0, 255, 0));

	ConsolaUtils::gotoxy(5, 9);
	cout << "Partida";
	ConsolaUtils::gotoxy(5 + comprimento*1.3, 9);
	cout << "Chegada";*/

	

	ConsolaUtils::gotoxy(0, 25);
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
			if (modo == 1)
				if (comando.at(0) == "lista")
					cout << dgv->lista();
				else if (comando.at(0) == "cria")
					dgv->cria(comando);
				else if (comando.at(0) == "entranocarro")
					dgv->entraNoCarro(comando);
				else if (comando.at(0) == "saidocarro")
					dgv->saiDoCarro(comando);
				else if (comando.at(0) == "campeonato") {
					dgv->comandoCampeonato(comando);
					modo = 2; continue;
				}
				else
					cout << "Comando nao encontrado" << endl;
			
			if (modo == 2) {
				if (comando.at(0) == "corrida")
					desenharPista(dgv->getComprimento(), dgv->getLargura());
				else if (comando.at(0) == "infocampeonato")
					dgv->infoCampeonato();
				else if (comando.at(0) == "scoreboard")
					dgv->scoreboard();
				else if (comando.at(0) == "passatempo")
					if (passatempo(comando)) { dgv->scoreboard(); continue; }
				else
					cout << "Comando nao encontrado" << endl;
				desenharPista(dgv->getComprimento(), dgv->getLargura());
			}

		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
	
	return false;
}

bool Consola::passatempo(vector<string> comando)
{
	int seg = 0;
	try {
		seg = stoi(comando.at(1));
	}
	catch(exception e){
		throw string("Usar: passatempo seg");
	}

	if(seg <= 0) throw string("Usar: passatempo seg");
	for (int i = 0; i < seg; i++) {
		desenharPista(dgv->getComprimento(), dgv->getLargura());
		cout << "Clique numa tecla para continuar\n";
		ConsolaUtils::getch();
		if (dgv->passaTempo())
			return true;
	}
	desenharPista(dgv->getComprimento(), dgv->getLargura());
	return false;
}
