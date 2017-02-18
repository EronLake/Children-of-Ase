#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "DialogueGui.h"

class RenderHelper
{
public:
	RenderHelper(QuadTree* QT);
	~RenderHelper();
	void initCamera(WorldObj* player);
	int draw_frame(WorldObj* obj);
	int sprite_up(WorldObj* obj);
	int sprite_down(WorldObj* obj);
	int sprite_left(WorldObj* obj);
	int sprite_right(WorldObj* obj);
	int sprite_update(WorldObj* obj);
	QuadTree* tree;
private:
	WorldObj* camera;
	DialogueGui* convoGui;
	std::vector<WorldObj*> objVec;

	//hold size of camera and map. first is width, second is height
	Vector2f cameraSize;
	Vector2f mapSize;
	Vector2f CamOffset;
	
};

