#pragma once
#include "common.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"

class PhysicsManager : public Manager {
public:
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~PhysicsManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};










/*class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();
	void playerAction(string task_name, WorldObj* player);
	void initTree(WorldObj* screen);
private:
	int move_up(WorldObj* player);
	int move_down(WorldObj* player);
	int move_left(WorldObj* player);
	int move_right(WorldObj* player);
	bool collision(WorldObj *player);
	vector <WorldObj*> objs;
	QuadTree* tree;
};*/