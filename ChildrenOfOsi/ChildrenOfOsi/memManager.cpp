#include "stdafx.h"
#include "memManager.h"


memManager::memManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("Memory Manager Objected Constructed");
	//////////////////////////////////////
}


memManager::~memManager()
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("Memory Manager Objected Destroyed");
	//////////////////////////////////////
}

void memManager::register_manager()
{
	//THIS IS WHAT YOU EDIT
	//////////////////////////////////////
	tBuffer->add_to_table("DUM", this);
	//////////////////////////////////////
}

void memManager::execute_task(Task* current_task)
{
	if (current_task->name == "Move_Up") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = move_up();
		//////////////////////////////////////
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
		int result = move_down();
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

//WRITE EQUIVLENT FUNCTIONS IN A SEPARATE CLASS FILE 
//////////////////////////////////////
int memManager::move_up()
{
	std::cout << "PhyM:Move Up" << std::endl;
	return 0;
}

int memManager::move_down()
{
	std::cout << "PhyM:Move Down" << std::endl;
	return 1;
}
//////////////////////////////////////


