#include "Consola.h"
#include "ConsolaUtils.h"


Consola::Consola(DGV* j) {
	this->dgv = j;
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

	ConsolaUtils::gotoxy(xlinha1-3, ylinha1-1);
	cout << "Partida";
	ConsolaUtils::gotoxy(xlinha1 - 3 + comprimento, ylinha1 - 1);

	cout << "Chegada";
	
	ConsolaUtils::gotoxy(xlinha1, ylinha1);
	ostringstream oss;
	for (int i = 0; i < comprimento; i++)
	{
		oss << "_";
	}
	cout << oss.str();
	ConsolaUtils::gotoxy(xlinha1, ylinha2);
	cout << oss.str();

	
	for (int i = ylinha1+1 ; i <= ylinha2; i++)
	{
		ConsolaUtils::gotoxy(xlinha1 + comprimento, i );
		if( i%2 == 0)ConsolaUtils::setTextColor(ConsolaUtils::AZUL);
		else ConsolaUtils::setTextColor(ConsolaUtils::PRETO);
		cout << "|";
	}
	ConsolaUtils::setTextColor(ConsolaUtils::PRETO);
	for (int i = ylinha1 + 1, j = 0; i <= ylinha2; i++,j++)
	{
		ConsolaUtils::gotoxy(xlinha1-2, i);
		char c = 'A' + j;
		cout << c << '|';
	}
	


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
			if (comando.at(0) == "lista") {
				cout << dgv->lista();
			}
			else if (comando.at(0) == "cria")
				dgv->cria(comando);
			else if (comando.at(0) == "pista")
				desenharPista(100, 10);
			else if (comando.at(0) == "entranocarro")
				dgv->entraNoCarro(comando);
			else if (comando.at(0) == "saidocarro")
				dgv->saiDoCarro(comando);
		}
		catch (string ex) {
			cout << ex << endl;
		}
	}
	
	return false;
}
