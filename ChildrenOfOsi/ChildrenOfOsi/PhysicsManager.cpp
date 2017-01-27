#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "PhysicsManager.h"



PhysicsManager::PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{

	LOG("PhysicsManager Object Constructed");
}

PhysicsManager::PhysicsManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _physicsQuadTree)
	: Manager(_mLog, _tBuffer)
{
	LOG("PhysicsManager W/QT Object Constructed");
	//init a movement obj 
	moveHelper = new Movement(_physicsQuadTree);
}


PhysicsManager::~PhysicsManager()
{

	LOG("PhysicsManager Object Destroyed");
	delete(moveHelper);
}

void PhysicsManager::register_manager()
{
	tBuffer->add_to_table("MOVE", this);
}

void PhysicsManager::execute_task(Task* current_task)
{
	int result;
	if (current_task->objToUpdate == NULL) {
		result = 1;
		LOG("Error: No player object");
		current_task->updateStatus("FAILED");
	}
	else {
		if (current_task->name == "Move_Up") {
			result = moveHelper->move_up(current_task->objToUpdate);
		}
		else if (current_task->name == "Move_Down") {
			result = moveHelper->move_down(current_task->objToUpdate);
		}
		else if (current_task->name == "Move_Left") {
			result = moveHelper->move_left(current_task->objToUpdate);
		}
		else if (current_task->name == "Move_Right") {
			result = moveHelper->move_right(current_task->objToUpdate);
		}
		else {
			result = 1;
			LOG("Error: Task name does not exist"); //perror?
		}
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);
}
