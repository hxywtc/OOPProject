#pragma once
#include "Common.h"
#include "Game.h"
#include "Player.h"

class Platform {
	Game* game;
	int id;
	Player* player[2];
	std::string color[2] = {"Black", "White"};
public:
	Platform() {};
	~Platform();
	void start();
	void init();
	void chooseGame();
	void choosePlayer(int id);
	void setPlayerStatus();
	void save();
	void load();
};