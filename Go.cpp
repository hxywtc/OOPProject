#include "Common.h"
#include "Go.h"
using namespace std;


Go::Go() {
	m_type = GO;
	//start();
}

void Go::start() {
	m_status.m_size = 9;
	m_status.m_turn = true;
	memset(m_status.m_board, 0, sizeof(m_status.m_board));
	m_history.clear();
	que.clear();
	m_history.push_back(m_status);
}

bool Go::breath(Point p, char ch) {
	visited[p.x][p.y] = true;
	que.push_back(p);
	bool res = false;
	for (int i = 0; i < 4; ++i) {
		int x = p.x + directx[i];
		int y = p.y + directy[i];
		if (0 <= x && x < m_status.m_size && 0 <= y && y < m_status.m_size) {
			if (int(m_status.m_board[x][y]) == 0) return true;
			if (m_status.m_board[x][y] == ch && !visited[x][y]) res |= breath(Point(x, y), ch); 
		}
	}
	return res;
}

void Go::set(Point point) {
	if (m_status.m_board[point.x][point.y]) return;
	if (m_status.m_turn) m_status.m_board[point.x][point.y] = 2;
	else m_status.m_board[point.x][point.y] = 1;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < m_status.m_size; ++i)
		for (int j = 0; j < m_status.m_size; ++j)
			if (!visited[i][j] && int(m_status.m_board[i][j]) > 0) {
				que.clear();
				if  (!breath(Point(i, j), m_status.m_board[i][j])) {
					for (auto p : que) {
						m_status.m_board[p.x][p.y] = 0;
					}
				}
			}
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

bool Go::draw() {
	if (m_history.size() >= 3) {
		m_history.pop_back();
		m_history.pop_back();
		m_status = *(m_history.end() - 1);
		return true;
	}
	return false;
}

void Go::stay() {
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

void Go::restart() {
	start();
}

bool Go::canPlace(int x, int y) {
	if (int(m_status.m_board[x][y]) > 0) return false;
	bool res = true;
	if (m_status.m_turn) m_status.m_board[x][y] = 2;
	else m_status.m_board[x][y] = 1;
	memset(visited, 0, sizeof(visited));
	que.clear();
	if (!breath(Point(x, y), m_status.m_board[x][y])) res = false;
	m_status.m_board[x][y] = 0;
	return res;
}

bool Go::canPlace() {
	return true;
}
	
int Go::checkWin() {
	return -1;
}

void Go::load(const std::string &_path) {
	m_history.clear();
	ifstream r;
	r.open(_path.c_str());
	Status s;
	while (r.read(reinterpret_cast<char *>(&s), sizeof(s))) {
		m_history.push_back(s);
	}
	m_status = *(m_history.end() - 1);
}

void Go::save(const std::string &_path) {
	ofstream w;
	w.open(_path.c_str());
	for (auto s : m_history) {
		w.write(reinterpret_cast<char *>(&s), sizeof(s));
	}
	w.close();
}
	
void Go::show() {
	cout << " 123456789\n";
	for (int i = 0; i < 9; ++i) {
		cout << i + 1;
		for (int j = 0; j < 9; ++j) {
			switch (m_status.m_board[i][j]) {
				case 0: cout << "."; break;
				case 1: cout << "o"; break;
				case 2: cout << "x"; break;
				default: cout << ".";
			}
		}
		cout << endl;
	}
}

Status& Go::getStatus() {
	return m_status;
}