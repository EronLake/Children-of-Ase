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

	void createTask(std::string task_name, std::string type, WorldObj * objToUpdate = NULL);
};

