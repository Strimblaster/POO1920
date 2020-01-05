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
	ConsolaUtils::setScreenSize(40, 170);
	while (nextCommand());
}

void Consola::desenharPista(int comprimentoMax, int largura) {
	int comprimento = 100;
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

	vector<Via*> posicoes = dgv->getPosicoes();
	int k = 0;
	for (Via* p : posicoes) {
		ConsolaUtils::gotoxy(xlinha1 -1 + (p->getPosicao() * comprimento)/comprimentoMax, ylinha1 + 1 + k);
		cout << p->getCarro()->getid();
		k++;
	}


	ConsolaUtils::gotoxy(xlinha1 + 70, ylinha2 + 3);
	cout << "Garagem: " << dgv->getGaragem();

	ConsolaUtils::gotoxy(0, ylinha2 + 3);
	cout << dgv->listaCarrosCampeonato();
	



	/*ConsolaUtils::drawLine(xlinha1-20, ylinha1, xlinha2+20, ylinha1, RGB(0, 0, 0));
	ConsolaUtils::drawLine(xlinha1-20, ylinha2, xlinha2+20, ylinha2, RGB(0, 0, 0));

	ConsolaUtils::drawLine(xlinha1, ylinha1, xlinha1, ylinha2, RGB(0, 0, 255));
	ConsolaUtils::drawLine(xlinha2, ylinha1, xlinha2, ylinha2, RGB(0, 255, 0));

	ConsolaUtils::gotoxy(5, 9);
	cout << "Partida";
	ConsolaUtils::gotoxy(5 + comprimento*1.3, 9);
	cout << "Chegada";*/

	

	ConsolaUtils::gotoxy(0, 35);
}

bool Consola::nextCommand() {
	if (modo == 1)
		cout << " ----- Simulador de carros - Modo 1 -----" << endl << endl;
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
		if (comando.at(0) == "sair")
			return false;
		try {
			if (modo == 1) {
				ConsolaUtils::clrscr();
				if (comando.at(0) == "lista")
					cout << dgv->lista();
				else if (comando.at(0) == "cria")
					dgv->cria(comando);
				else if (comando.at(0) == "apaga")
					dgv->apaga(comando);
				else if (comando.at(0) == "carregaP")
					dgv->carregaP(comando);
				else if (comando.at(0) == "carregaC")
					dgv->carregaC(comando);
				else if (comando.at(0) == "carregaA")
					dgv->carregaA(comando);
				else if (comando.at(0) == "entranocarro")
					dgv->entraNoCarro(comando);
				else if (comando.at(0) == "saidocarro")
					dgv->saiDoCarro(comando);
				else if (comando.at(0) == "campeonato") {
					dgv->comandoCampeonato(comando);
					modo = 2;
					cout << endl << "----- Simulador de carros - Modo 2 -----" << endl;
					continue;
				}
				else if (comando.at(0) == "help")
					cout << "Lista de comandos - Modo 1:\nlista\ncria\napaga\ncarregaP\ncarregaC\ncarregaA\nentranocarro\nsaidocarro\ncampeonato\n";
				else
					cout << "Comando nao encontrado" << endl;
			}
			
			if (modo == 2) {
				try {
					if (comando.at(0) == "corrida") {
						if (dgv->proxCorrida())
							modo = 1;
					}
					else if (comando.at(0) == "infocampeonato") {
						ConsolaUtils::clrscr();
						ConsolaUtils::gotoxy(0, 0);
						dgv->infoCampeonato();
						if (dgv->corridaADecorrer()) {
							cout << endl << endl << "Clique numa tecla para voltar";
							ConsolaUtils::getch();
						}
					}

					else if (comando.at(0) == "scoreboard") {
						ConsolaUtils::clrscr();
						ConsolaUtils::gotoxy(0, 0);
						dgv->scoreboard();
						if (dgv->corridaADecorrer()) {
							cout << endl << endl << "Clique numa tecla para voltar";
							ConsolaUtils::getch();
						}
					}
					else if (comando.at(0) == "passatempo") {
						if (passatempo(comando)) {
							ConsolaUtils::clrscr();
							cout << "A corrida terminou!" << endl << endl;
							cout << dgv->listaCarrosCampeonato();
							continue;
						}
					}
					else if (comando.at(0) == "listacarros") {
						ConsolaUtils::clrscr();
						cout << dgv->listaCarrosCampeonato();
						cout << endl << "Prima qualquer tecla para continuar" << endl;
						ConsolaUtils::getch();
					}
					else if (comando.at(0) == "carregabat") {
						dgv->carregaCarro(comando);
					}
					else if (comando.at(0) == "carregatudo") {
						dgv->carregaTudo();
					}
					else if (comando.at(0) == "destroi") {
						dgv->destroiCarro(comando);
					}
					else if (comando.at(0) == "acidente") {
						dgv->acidente(comando);
					}
					else if (comando.at(0) == "stop") {
						dgv->stop(comando);
					}
					else if (comando.at(0) == "log") {
						ConsolaUtils::clrscr();
						for (string s : dgv->getLog()) {
							cout << s;
						}
						cout << endl << endl << "Clique numa tecla para voltar";
						ConsolaUtils::getch();
					}
					else if (comando.at(0) == "help")
						cout << "Lista de comandos - Modo 2:\ncorrida\ninfocampeonato\nscoreboard\npassatempo\nlistacarros\n";
					else
						cout << "Comando nao encontrado" << endl;
					if (dgv->corridaADecorrer())
						desenharPista(dgv->getComprimento(), dgv->getLargura());
				}
				catch (string ex) {
					cout << ex << endl << "Prima qualquer tecla para continuar" << endl;
					ConsolaUtils::getch();
				}
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
	if (!dgv->corridaADecorrer()) throw string("Nenhuma corrida a decorrer");
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

