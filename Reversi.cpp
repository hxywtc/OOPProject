#include "Common.h"
#include "Reversi.h"
using namespace std;

Reversi::Reversi() {
	m_type = REVERSI;
	//start();
}

void Reversi::start() {
	m_status.m_size = 8;
	m_status.m_turn = true;
	memset(m_status.m_board, 0, sizeof(m_status.m_board));
	m_status.m_board[3][3] = m_status.m_board[4][4] = 1;
	m_status.m_board[3][4] = m_status.m_board[4][3] = 2;
	m_history.clear();
	m_history.push_back(m_status);
}

void Reversi::set(Point point) {
	if (m_status.m_board[point.x][point.y]) return;
	if (m_status.m_turn) m_status.m_board[point.x][point.y] = 2;
	else m_status.m_board[point.x][point.y] = 1;
	for (int i = 0; i < 8; ++i) {
		int xx = point.x + directx[i];
		int yy = point.y + directy[i];
		//cout <<"**********"<< x <<" "<<y<< " " << directx[i] << " " << directy[i] << " " << m_status.m_size << "\n";
		if (0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && 
		int(m_status.m_board[xx][yy]) > 0 && int(m_status.m_board[xx][yy]) - int(m_status.m_turn) != 1) {
			while (0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && 
			int(m_status.m_board[xx][yy]) > 0 && int(m_status.m_board[xx][yy]) - int(m_status.m_turn) != 1) {
				xx += directx[i];
				yy += directy[i];
			}
			if ((0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && int(m_status.m_board[xx][yy]) > 0)
			&& (int(m_status.m_board[xx][yy]) - int(m_status.m_turn) == 1)) {
				for (xx -= directx[i], yy -= directy[i]; xx != point.x || yy !=point.y; xx -= directx[i], yy -= directy[i]) {
					m_status.m_board[xx][yy] = 3 - int(m_status.m_board[xx][yy]);
				}
			}
		}
	}
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

bool Reversi::draw() {
	if (m_history.size() >= 3) {
		m_history.pop_back();
		m_history.pop_back();
		m_status = *(m_history.end() - 1);
		return true;
	}
	return false;
}

void Reversi::stay() {
	m_status.m_turn = !(m_status.m_turn);
	m_history.push_back(m_status);
}

void Reversi::restart() {
	start();
}

bool Reversi::canPlace(int x, int y) {
	if (!(0 <= x && x < m_status.m_size && 0 <= y && y < m_status.m_size)) return false;
	int xx, yy;
	for (int i = 0; i < 8; ++i) {
		xx = x + directx[i];
		yy = y + directy[i];
		//cout <<"**********"<< x <<" "<<y<< " " << directx[i] << " " << directy[i] << " " << m_status.m_size << "\n";
		if (0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && 
		int(m_status.m_board[xx][yy]) > 0 && int(m_status.m_board[xx][yy]) - int(m_status.m_turn) != 1) {
			while (0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && 
			int(m_status.m_board[xx][yy]) > 0 && int(m_status.m_board[xx][yy]) - int(m_status.m_turn) != 1) {
				xx += directx[i];
				yy += directy[i];
			}
			if ((0 <= xx && xx < m_status.m_size && 0 <= yy && yy < m_status.m_size && int(m_status.m_board[xx][yy]) > 0)
			&& (int(m_status.m_board[xx][yy]) - int(m_status.m_turn) == 1)) return true;
		}
	}
	return false;
}

bool Reversi::canPlace() {
	for (int i = 0; i < m_status.m_size; ++i)
		for (int j = 0; j < m_status.m_size; ++j)
			if (canPlace(i, j)) return true;
	return false;
}

int Reversi::calcWin() {
	int count[2]={0};
	for (int i = 0; i < m_status.m_size; ++i)
		for (int j = 0; j < m_status.m_size; ++j) {
			if (!m_status.m_board[i][j]) count[m_status.m_board[i][j] - 1]++;
		}
	if (count[1] == count[0]) return 2;
	return (count[1] > count[0]);
}
	
int Reversi::checkWin() {
	bool flag;
	if (!canPlace()) {
		m_status.m_turn = !(m_status.m_turn);
		if (!canPlace()) return calcWin();
		m_status.m_turn = !(m_status.m_turn);
	}
	return -1;
}

void Reversi::load(const std::string &_path) {
	m_history.clear();
	ifstream r;
	r.open(_path.c_str());
	Status s;
	while (r.read(reinterpret_cast<char *>(&s), sizeof(s))) {
		m_history.push_back(s);
	}
	m_status = *(m_history.end() - 1);
}
	
void Reversi::save(const std::string &_path) {
	ofstream w;
	w.open(_path.c_str());
	for (auto s : m_history) {
		w.write(reinterpret_cast<char *>(&s), sizeof(s));
	}
	w.close();
}
	
void Reversi::show() {
	cout << " 12345678\n";
	for (int i = 0; i < 8; ++i) {
		cout << i + 1;
		for (int j = 0; j < 8; ++j) {
			switch (m_status.m_board[i][j]) {
				case 0: if (canPlace(i, j)) cout << "#";
						else 
						cout << "."; 
						break;
				case 1: cout << "o"; break;
				case 2: cout << "x"; break;
				default: cout << ".";
			}
		}
		cout << endl;
	}
}

Status& Reversi::getStatus() {
	return m_status;
}