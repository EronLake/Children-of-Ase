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

class PhysicsManager;

class Movement {
public:
	Movement(QuadTree* QT);
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
	int melee(WorldObj* obj);
	int specialAttack(WorldObj* obj);
	int attack(WorldObj* obj);
	int meleeSwing(WorldObj* obj);
	//void init_task_map();
    QuadTree* tree;
	RiverObj* rivObj;
	PhysicsManager* manager;
	float speed_magnifier = 2.0f;
	float moveSpeed;
	float diagSpeed;
	float diagXSpeed; 
	float diagYSpeed;
	CombatController combatControl;

private:
	bool collision(WorldObj* recA, WorldObj* recB);
	bool lineCollision(Line l1, Line l2);
	bool interaction(Player* recA, WorldObj* recB);
	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }
	//hold obj to check with. init before each move funcs call
	std::vector<WorldObj*> objVec;
};
