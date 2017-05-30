#pragma once
#include "stdafx.h"
#include "common.h"
#include "QuadTree.h"
#include "Task.h"
#include "Player.h"
#include "CheckClass.h"
#include "DialogueController.h"
#include "CombatController.h"
#include "RiverObj.h"
#include "AIController.h"
#include "PlayerActExecFunctions.h"
#include "UniformGrid.h"

#include <thread>
#include <future>

class PhysicsManager;

class Movement {
public:
	Movement(QuadTree* QT, UniformGrid<Line>* _UG, RiverObj* _rivObj, UniformGrid<WorldObj>* _worldobj_grid);
	~Movement();
	//void playerAction(string task_name, WorldObj* player);
	//static void initTree(WorldObj* screen);
	int move_up(WorldObj* obj);
	int move_up_right(WorldObj* obj);
	int move_up_left(WorldObj* obj);
	int move_down(WorldObj* obj);
	int move_down_right(WorldObj* obj);
	int move_down_left(WorldObj* obj);
	int move_left(WorldObj* obj);
	int move_right(WorldObj* obj);
//	int move_toward(WorldObj* obj);
	int talk(WorldObj* obj);
	int attack(WorldObj* obj);
	bool collision(WorldObj* recA, WorldObj* recB);
	bool col_thread(WorldObj* recA, WorldObj* recB);
	
	
	//void init_task_map();
    QuadTree* tree;
	UniformGrid<Line>* grid;
	UniformGrid<WorldObj>* world_grid;
	RiverObj* rivObj;
	PhysicsManager* manager;

	float speed_magnifier = 1.0f;
	float moveSpeed;
	float diagSpeed;
	float diagXSpeed; 
	float diagYSpeed;

	WorldObj player_clone;
	bool set_player_clone;

	static bool interaction(Player* recA, WorldObj* recB);
	static bool coordOverlap(float value, float min, float max) { return (value >= min) && (value <= max); }

private:
	

	bool lineCollision(Line* l1, Line* l2);
	bool shouldCheckLineCollision(Point target, Point dest1, Point dest2, int dist);
	
	
	//hold obj to check with. init before each move funcs call
	std::vector<WorldObj*> objVec;
	std::vector<Line*> lineVec;
};
