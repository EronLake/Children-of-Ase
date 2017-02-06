#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
class RenderHelper
{
public:
	RenderHelper();
	~RenderHelper();
	void getRenderObjs(vector<WorldObj*> collidable);
	bool Collision(WorldObj* recA, WorldObj* recB);
	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }
private:
	WorldObj* Camera;
	std::vector<WorldObj*> objVec;
};

