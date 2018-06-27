#pragma once
#include "Common.h"
#include "Game.h"

class Reversi : public Game {
public:
	Reversi();
	void start();
	void set(Point point);
	bool draw();
	void stay();
	void restart();
	int checkWin();
	void load(const std::string &_path);
	void save(const std::string &_path);
	void show();
	Status& getStatus();
	bool canPlace();
	bool canPlace(int x, int y);
	int calcWin();
};