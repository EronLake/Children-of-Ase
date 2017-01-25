#pragma once
#include "common.h"
#include "QuadTree.h"
class Movement {
public:
	Movement();
	~Movement();
	//void playerAction(string task_name, WorldObj* player);
	static void initTree(WorldObj* screen);
	static int move_up(WorldObj* player);
	static int move_down(WorldObj* player);
	static int move_left(WorldObj* player);
	static int move_right(WorldObj* player);
	
private:
	static std::vector <WorldObj*> objs;
	static QuadTree* tree;
	static bool collision(WorldObj *player);
};