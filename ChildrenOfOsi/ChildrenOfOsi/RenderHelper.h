#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "DialogueGui.h"
#include "DialogueController.h"
#include "GameMap.h"

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
	int sprite_idle(WorldObj* obj);
	int sprite_update(WorldObj* obj);
	int drawDiaGui(WorldObj* obj);
	int setSwordGlow(WorldObj* obj);
	int setHeartGlow(WorldObj* obj);
	int setFaceGlow(WorldObj* obj);
	int setQuestionGlow(WorldObj* obj);
	void sortVec();
	bool compY(WorldObj* a, WorldObj* b);
	int updateGuiText(WorldObj* obj);
	QuadTree* tree;
	//need this for map editor
	WorldObj* camera;
private:
	
	DialogueGui* convoGui;
	GameMap* gmap;
	std::vector<WorldObj*> objVec;

	//hold size of camera and map. first is width, second is height
	Vector2f cameraSize;
	Vector2f mapSize;
	Vector2f CamOffset;
	
};

