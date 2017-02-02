#include "stdafx.h"
#include "ChildrenOfOsi.h"


ChildrenOfOsi::ChildrenOfOsi(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	LOG("ChildrenOfOsi Object Constructed");
}


ChildrenOfOsi::~ChildrenOfOsi()
{
	LOG("ChildrenOfOsi Object Destroyed");
}
//////////////////////////////////////////////////////
//----------------------------------------------------


void ChildrenOfOsi::move_up(WorldObj * player)
{
	createTask("Move_Up", "MOVE", player);
}

void ChildrenOfOsi::move_left(WorldObj * player)
{
	createTask("Move_Left", "MOVE", player);
}

void ChildrenOfOsi::move_down(WorldObj * player)
{
	createTask("Move_Down", "MOVE", player);
}

void ChildrenOfOsi::move_right(WorldObj * player)
{
	createTask("Move_Right", "MOVE", player);
}

void ChildrenOfOsi::move_out(WorldObj * player)
{
	createTask("Move_Out", "MOVE", player);
}
//----------------------------------------------------


//----------------------------------------------------
void ChildrenOfOsi::createTask(std::string task_name, std::string type, WorldObj * objToUpdate)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, objToUpdate);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}