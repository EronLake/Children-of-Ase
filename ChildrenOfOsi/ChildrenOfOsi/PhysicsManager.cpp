#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "PhysicsManager.h"
#include "Movement.h"



PhysicsManager::PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{

	LOG("PhysicsManager Object Constructed");
}


PhysicsManager::~PhysicsManager()
{

	LOG("PhysicsManager Object Destroyed");

}

void PhysicsManager::register_manager()
{
	tBuffer->add_to_table("MOVE", this);
}

void PhysicsManager::execute_task(Task* current_task)
{
	int result;
	if (player == NULL) {
		result = 1;
		LOG("Error: No player object");
		current_task->updateStatus("FAILED");
	}
	else {
		if (current_task->name == "Move_Up") {
			result = Movement::move_up(player);
		} 
		else if (current_task->name == "Move_Down") {
			result = Movement::move_down(player);
		}
		else if (current_task->name == "Move_Left") {
			result = Movement::move_left(player);
		}
		else if (current_task->name == "Move_Right") {
			result = Movement::move_right(player);
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

