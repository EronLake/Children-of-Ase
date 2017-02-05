#pragma once
#include "common.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"


class ChildrenOfOsi
{
private:
	MessageLog* mLog;
	TaskBuffer* tBuffer;
public:
	ChildrenOfOsi(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~ChildrenOfOsi();

	//functions for moving
	void move_up(WorldObj * player);
	void move_left(WorldObj * player);
	void move_down(WorldObj * player);
	void move_right(WorldObj * player);
	void move_out(WorldObj * player);

	//functions for creating objects in memory
	void add_hero(float x, float y, bool col);
    void add_soldier(float x, float y, bool col);
	void add_projectile(float x, float y, bool col, int d);
	void add_spl_soldier(float x, float y, bool col);
	void add_livingObj(float x, float y, bool col);
	void add_worldObj(float x, float y, bool col);
	void add_npc(float x, float y, bool col);

	void createTask(std::string task_name, std::string type, WorldObj * objToUpdate = NULL);
	void ChildrenOfOsi::createTaskWithParams(std::string task_name, std::string type, float x, float y, bool col);
	void ChildrenOfOsi::createTaskForProjectile(std::string task_name, std::string type, float x, float y, bool col, int d);
};

