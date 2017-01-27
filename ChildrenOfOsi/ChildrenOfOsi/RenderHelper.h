#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
class RenderHelper
{
public:
	RenderHelper(QuadTree* QT);
	~RenderHelper();
private:
	QuadTree* tree;
	std::vector<WorldObj*> objVec;
};

