#pragma once
#include "Common.h"

class Player {
protected:
	Status m_status;
	PlayerType m_type;
public:
	int idx;
	virtual Point place() = 0;
	virtual void setStatus(const Status& _status) = 0;
	virtual bool isHuman() = 0;
};