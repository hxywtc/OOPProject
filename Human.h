#pragma once
#include "Common.h"
#include "Player.h"

class Human : public Player {
public:
	Human();
	Point place();
	void setStatus(const Status& _status);
	bool isHuman();
};