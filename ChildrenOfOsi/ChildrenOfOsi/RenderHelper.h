#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
class RenderHelper
{
public:
	RenderHelper(QuadTree* QT);
	~RenderHelper();
	void initCamera(WorldObj* player);
	int draw_frame(WorldObj* obj);
	int sprite_change(WorldObj* obj);
	int sprite_update(WorldObj* obj);
	QuadTree* tree;
private:
	WorldObj* camera;
	std::vector<WorldObj*> objVec;
};

