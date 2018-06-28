#include "Common.h"
#include "Platform.h"
#include "Gobang.h"
#include "Human.h"
#include "GobangAI.h"
#include "Reversi.h"
#include "Go.h"
using namespace std;

Platform::~Platform() {
	delete game;
	delete player[0];
	delete player[1];
}

void Platform::chooseGame() {
	cout << "Please choose a game (1-3):\n1. REVERSI\n2. GO\n3. GOBANG\n";
	int inp;
	cin >> inp;
	switch (inp) {
		case 1: game = new Reversi(); break;
		case 2: game = new Go(); break;
		case 3: game = new Gobang(); break;
		default: cout << "Input Error!\n"; chooseGame();
	}
}

void Platform::choosePlayer(int id) {
	cout << "Please choose player" << id + 1 << " (" << color[id] << ") (1-2):\n1. COMPUTER\n2. HUMAN\n";
	int inp;
	cin >> inp;
	switch (inp) {
		case 1: player[id] = new GobangAI(); 
				player[id]->idx = id + 1;
				break;
		case 2: player[id] = new Human();
				player[id]->idx = id + 1;
				break;
		default: cout << "Input Error!\n"; choosePlayer(id);
	}
}

void Platform::setPlayerStatus() {
	for (int i = 0; i < 2; ++i)
		player[i]->setStatus(game->getStatus());
}

void Platform::init() {
	id = 0;
	chooseGame();
	choosePlayer(0);
	choosePlayer(1);
	game->start();
}

void Platform::save() {
	cout << "Name of this Record:\n";
	string fname;
	cin >> fname;
	game->save(fname);
}

void Platform::load() {
	cout << "Path for loading:\n";
	string path;
	cin >> path;
	game->load(path);
	if (game->getStatus().m_turn) id = 0;
	else id = 1;
}

void Platform::start() {
	int inp;
	Point p;
	for (;;) {
		cout << "**************Board Platform**************\n1. START A GAME\n2. EXIT\n";
		//int inp;
		cin >> inp;
		if (inp == 2) break;
		if (inp != 1) {
			cout << "Input Error!\n";
			continue;
		}
		init();
		for ( ; ; id = 1 - id) {
			setPlayerStatus();
			if (game->canPlace())
				if (player[id]->isHuman()) {
					cout << "**************Board Platform**************\n";
					cout << color[id] << "'s turn (1-6):\n1. PLACE\n2. RETRACT\n3. RESTART\n4. SAVE\n5. LOAD\n6. EXIT\n";
					game->show();
					//int inp;
					cin >> inp;	
					if (inp == 6) break;

					switch (inp) {
						case 1: p = player[id]->place();
								if (p.x == -1) {
									game->stay();
								} else {
									if (game->canPlace(p.x, p.y)) {
										game->set(p);
									} else {
										cout << "Can not Place here!\n";
										id = 1 - id;
									}
								}
								break;
						case 2: if (game->draw()) {
									id = 1 - id;
								} else {
									cout << "Can not Retract!\n";
									id = 1 - id;
								}
								break;
						case 3: game->restart();
								id = 1;
								break;
						case 4: save();
								id = 1 - id;
								break;
						case 5: load();
								id = 1 - id;
								break;
						default: cout << "Input Error!\n";
								 id = 1 - id;
					}
					
				} else {
					game->show();
					cout << color[id] << "'s turn:\n";
					Point p = player[id]->place();
					if (p.x == -1) {
						game->stay();
						cout << "Stay\n";
					} else {
						game->set(p);
						cout << "Place (" << p.x + 1 << ", " << p.y + 1 << ")\n";
					}
				}
			else {
				game->stay();
				game->show();
				cout << color[id] << "'s turn:\n";
				cout << "Stay\n";
			}
			inp = game->checkWin();
			//cout<<"now game "<<inp<<endl;
			if (inp != -1) {
				game->show();
				if (inp == 2) {
					cout << "Tie!\n";
					break;
				} else {
					cout << "Player" << inp + 1 << "(" << color[inp] << ") wins!\n";
					break;
				} 
			}
		}
	}
}