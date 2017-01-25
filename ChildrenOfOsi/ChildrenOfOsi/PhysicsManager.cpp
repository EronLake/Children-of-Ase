#pragma comment(lib, "user32.lib")

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
	tBuffer->add_to_table("MOV", this);
}

void PhysicsManager::execute_task(Task* current_task)
{
	WorldObj* player = new WorldObj(0.0,0.0,false);
	if (current_task->name == "Move_Up") {

		//int result = move_up();
		int result = 0;
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "Move_Down") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		//int result = move_down(); r
		int result = 0;
		//////////////////////////////////////
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else
	{
		LOG("Error: Task name does not exist"); //perror?
	}
}

