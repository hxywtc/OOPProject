#pragma once 
#include "Common.h"
#include "Player.h"

class AI : public Player {
public:
	AI();
	virtual Point place() = 0;
	void setStatus(const Status& _status);
	bool isHuman();
};