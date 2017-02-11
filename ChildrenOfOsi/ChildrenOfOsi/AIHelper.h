#pragma once
#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
class AIHelper
{
public:
	AIHelper();
	AIHelper(WorldObj* obj);
	~AIHelper();
	int Astar(WorldObj* player);

private:
	//std::vector<WorldObj*> objVec;
};

