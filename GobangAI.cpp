#include "Common.h"
#include "GobangAI.h"

#define MAX_SCORE 9999999
#define MIN_SCORE -99999999

using namespace std;

GobangAI::GobangAI() {

}

Point GobangAI::place() {
	int search_depth=3;
	float best = MIN_SCORE;
	Point best_point;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			//Loop on all position
			if (int(m_status.m_board[i][j]) == 0) {
				//Given a position, find its value
				m_status.m_board[i][j] = idx;
				float tmp_score = min_search(m_status, search_depth-1, idx, MAX_SCORE, MIN_SCORE);
				if (tmp_score > best) {
					best = tmp_score;
					best_point.x = i;
					best_point.y = j;
				}
				m_status.m_board[i][j] = 0;
			}
		}
	}
	return best_point;
}

float min_search(Status& status, int depth, int idx, float alpha, float beta) {
	float tmp_score = evaluation(status, idx);
	float best = MAX_SCORE;
	if (depth <= 0) return tmp_score;

	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (int(status.m_board[i][j]) == 0){
				status.m_board[i][j] = 3-idx;
				float tmp_score = max_search(status, depth-1, idx, best < alpha ? best : alpha, beta);
				status.m_board[i][j] = 0;
				if (tmp_score < best) {
					best = tmp_score;
				}
				if (tmp_score < beta) break;
 
			}
		}
	}

	return best;
}

float max_search(Status& status, int depth, int idx, float alpha, float beta) {
	float tmp_score = evaluation(status, idx);
	if (depth <= 0) return tmp_score;

	float best = MIN_SCORE;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (int(status.m_board[i][j]) == 0) {
				status.m_board[i][j] = idx;
				float tmp_score = min_search(status, depth-1, idx, alpha, best > beta ? best : beta);
				status.m_board[i][j] = 0;
				if (tmp_score > best) {
					best = tmp_score;
				}

				if (tmp_score > alpha) break;
			}
		}
	}
	return best;
}


float evaluation(Status& tmp_status, int idx) {
	int res = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (int(tmp_status.m_board[i][j]) != 0) {
				//left row;
				bool flag1 = false, flag2 = false;
				int x = j, y = i;
				int cnt = 1;
				int col = x, row = y;
				while (--col > -1 && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (col > -1 && int(tmp_status.m_board[row][col]) == 0) flag1 = true;
				col = x; row = y;

				while (++col < MAX_SIZE && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (col < MAX_SIZE && int(tmp_status.m_board[row][col]) == 0) flag2 = true;

				if (flag1 && flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) * cnt * cnt;
				else if (flag1 || flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) * cnt * cnt / 4;
				if (cnt >= 5) res = (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) * MAX_SCORE/2;

				col = x; row = y;
				cnt = 1; flag1 = false; flag2 = false;
				while (--row > -1 && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (row > -1 && int(tmp_status.m_board[row][col]) == 0) flag1=true;
				col = x; row = y;

				while (++row < MAX_SIZE && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (row < MAX_SIZE && int(tmp_status.m_board[row][col]) == 0) flag2 = true;

				if (flag1 && flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *cnt * cnt;
				else if (flag1 || flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *cnt * cnt / 4;
				if (cnt >= 5) res = (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *MAX_SCORE/2;

				col = x; row = y;
				cnt = 1; flag1 = false; flag2 = false;
				while (--col > -1 && --row > -1 && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (col > -1 && row > -1 && int(tmp_status.m_board[row][col]) == 0) flag1 = true;
				col = x; row = y;

				while (++col && ++row < MAX_SIZE && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (col < MAX_SIZE && row < MAX_SIZE && int(tmp_status.m_board[row][col]) == 0) flag2 = true;
				if (flag1 && flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *cnt * cnt;
				else if (flag1 || flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *cnt * cnt /4 ;
				if (cnt >= 5) res = (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *MAX_SCORE/2;

				col = x; row = y;
				cnt = 1; flag1 = false; flag2 = false;
				while (++row < MAX_SIZE && --col > -1 && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (row < MAX_SIZE && col > -1 && int(tmp_status.m_board[row][col]) == 0) flag1 = true;
				col = x; row = y;

				while (--row > -1 && ++col < MAX_SIZE && tmp_status.m_board[row][col] == tmp_status.m_board[y][x]) ++cnt;
				if (row > -1 && col < MAX_SIZE && int(tmp_status.m_board[row][col]) == 0) flag2 = true;
				if (flag1 && flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3)* (2 * idx - 3) * cnt * cnt;
				else if (flag1 || flag2) res += (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *cnt * cnt / 4;
				if (cnt >= 5) res = (int(tmp_status.m_board[i][j]) * 2 - 3) * (2 * idx - 3) *MAX_SCORE/2;


			}
		}
	}
	return res;
}