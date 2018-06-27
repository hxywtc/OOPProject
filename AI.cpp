#include "Common.h"
#include "AI.h"

using namespace std;

AI::AI() {
	m_type = COMPUTER;
}

void AI::setStatus(const Status& _status) {
	m_status = _status;
}

bool AI::isHuman() {
	return false;
}