#include "Common.h"
#include "Human.h"

using namespace std;

Human::Human() {
	m_type = HUMAN;
}

Point Human::place() {
	Point point;
	cout << "Please input the position:\n";
	cin >> point.x >> point.y;
	if (0 < point.x && point.x <= m_status.m_size && 0 < point.y && point.y <= m_status.m_size && !m_status.m_board[--point.x][--point.y]) {
		return point;
	}
	else {
		cout << "Input Error!\n";
		return place();
	}
}

void Human::setStatus(const Status& _status) {
	m_status = _status;
}

bool Human::isHuman() {
	return true;
}