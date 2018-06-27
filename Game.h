#pragma once
#include "Common.h"

class Game {
protected:
	GameType m_type;
	Status m_status;
	std::vector<Status> m_history;

public:
	virtual void start() = 0;
	virtual void set(Point _point) = 0;
	virtual bool draw() = 0;
	virtual void stay() = 0;
	virtual void restart() = 0;
	virtual int checkWin() = 0;
	virtual void load(const std::string &_path) = 0;
	virtual void save(const std::string &_path) = 0;
	virtual void show() = 0;
	virtual Status& getStatus() = 0;
	virtual bool canPlace() = 0;
	virtual bool canPlace(int x, int y) = 0;
};