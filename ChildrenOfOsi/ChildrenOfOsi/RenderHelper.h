#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "DialogueGui.h"
#include "DialogueController.h"
#include "GameMap.h"
#include "Containers.h"
#include "CheckClass.h"
#include "HUD.h"
#include "common.h"

class RenderManager;
class RenderHelper
{
public:
	RenderHelper(QuadTree* QT);
	~RenderHelper();
	void initCamera(WorldObj* player);
	void initCameraFull(WorldObj* player);
	int init_map(WorldObj* obj);
	int draw_frame(WorldObj* obj);
	int sprite_up(WorldObj* obj);
	int sprite_down(WorldObj* obj);
	int sprite_left(WorldObj* obj);
	int sprite_right(WorldObj* obj);
	int sprite_atk(WorldObj* obj);
	int sprite_spin_atk(WorldObj* obj);
	int sprite_fire_atk(WorldObj* obj);
	int sprite_hurt(WorldObj* obj);
	int sprite_idle(WorldObj* obj);
	int sprite_update(WorldObj* obj);
	int drawDiaGui(WorldObj* obj);
	int drawHUD(WorldObj* obj);
	int setSwordGlow(WorldObj* obj);
	int setHeartGlow(WorldObj* obj);
	int setFaceGlow(WorldObj* obj);
	int setQuestionGlow(WorldObj* obj);
	void sortVec();
	bool compY(WorldObj* a, WorldObj* b);
	QuadTree* tree;
	//need this for map editor
	WorldObj* camera;
	WorldObj* fullBound;
	RenderManager* manager;
private:
	
	DialogueGui* convoGui;
	HUD* hud_ptr;
	GameMap* gmap;
	std::vector<WorldObj*> objVec;
	std::vector<WorldObj*> fullVec;

	//hold size of camera and map. first is width, second is height
	Vector2f cameraSize;
	Vector2f mapSize;
	Vector2f CamOffset;
	
};

