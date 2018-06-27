#pragma once
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>

#define MAX_SIZE 9

enum GameType {REVERSI, GO, GOBANG};
enum PlayerType {COMPUTER, HUMAN};

struct Point {
	int x, y;
};

struct Status {
	int m_size;
	bool m_turn;
	char m_board[MAX_SIZE][MAX_SIZE];
	void operator= (const Status& _status) {
		m_size = _status.m_size;
		m_turn = _status.m_turn;
		for (int i = 0; i < m_size; ++i)
			for (int j = 0; j < m_size; ++j)
				m_board[i][j] = _status.m_board[i][j];
	}
};

static int directx[8] = {1, 1,  0,  -1, -1, -1, 0, 1};
static int directy[8] = {0, -1, -1, -1, 0,  1,  1, 1};
