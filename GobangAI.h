#pragma once
#include "AI.h"

class GobangAI : public AI {
public:
	GobangAI();
	Point place();
};

float min_search(Status& _status, int depth, int idx, float alpha, float beta);
float max_search(Status& _status, int depth, int idx, float alpha, float beta);
float evaluation(Status& _status, int idx);