#include "Common.h"
#include "Gobang.h"
using namespace std;

Gobang::Gobang() {
	m_type = GOBANG;
	start();
}

void Gobang::start() {
	m_status.m_size = 9;
	m_status.m_turn = true;
	memset(m_status.m_board, 0, sizeof(m_status.m_board));
	m_history.clear();
	m_history.push_back(m_status);
}

void Gobang::set(Point point) {
	if (m_status.m_board[point.x][point.y]) return;
	if (m_status.m_turn) m_status.m_board[point.x][point.y] = 2;
	else m_status.m_board[point.x][point.y] = 1;
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

bool Gobang::draw() {
	if (m_history.size() >= 3) {
		m_history.pop_back();
		m_history.pop_back();
		m_status = *(m_history.end() - 1);
		return true;
	}
	return false;
}

void Gobang::stay() {
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

void Gobang::restart() {
	start();
}
	
int Gobang::checkWin() {
	bool flag;
	for (int i = 0; i < m_status.m_size; ++i)
		for (int j = 0; j < m_status.m_size; ++j) {
			if (!m_status.m_board[i][j]) continue;
			if (i + 4 < m_status.m_size) {
				flag = true;
				for (int k = i + 1; k <= i + 4; ++k) {
					if (m_status.m_board[k][j] != m_status.m_board[i][j]) {
						flag = false;
						break;
					}
				}
				if (flag) return m_status.m_board[i][j] - 1;
			}
			if (j + 4 < m_status.m_size) {
				flag = true;
				for (int k = j + 1; k <= j + 4; ++k) {
					if (m_status.m_board[i][k] != m_status.m_board[i][j]) {
						flag = false;
						break;
					}
				}
				if (flag) return m_status.m_board[i][j] - 1;
			}
			if (i + 4 < m_status.m_size && j + 4 < m_status.m_size) {
				flag = true;
				for (int k = 1; k <= 4; ++k) {
					if (m_status.m_board[i + k][j + k] != m_status.m_board[i][j]) {
						flag = false;
						break;
					}
				}
				if (flag) return m_status.m_board[i][j] - 1;
			}
			if (i + 4 < m_status.m_size && j - 4 >= 0) {
				flag = true;
				for (int k = 1; k <= 4; ++k) {
					if (m_status.m_board[i + k][j - k] != m_status.m_board[i][j]) {
						flag = false;
						break;
					}
				}
				if (flag) return m_status.m_board[i][j] - 1;
			}
		}
	return -1;
}

void Gobang::load(const std::string &_path) {
	m_history.clear();
	ifstream r;
	r.open(_path.c_str());
	Status s;
	while (r.read(reinterpret_cast<char *>(&s), sizeof(s))) {
		m_history.push_back(s);
	}
	m_status = *(m_history.end() - 1);
}
	
void Gobang::save(const std::string &_path) {
	ofstream w;
	w.open(_path.c_str());
	for (auto s : m_history) {
		w.write(reinterpret_cast<char *>(&s), sizeof(s));
	}
	w.close();
}
	
void Gobang::show() {
	cout << " 123456789\n";
	for (int i = 0; i < 9; ++i) {
		cout << i + 1;
		for (int j = 0; j < 9; ++j) {
			switch (m_status.m_board[i][j]) {
				case 0: cout << "."; break;
				case 1: cout << "o"; break;
				case 2: cout << "x"; break;
			}
		}
		cout << endl;
	}
}

Status& Gobang::getStatus() {
	return m_status;
}