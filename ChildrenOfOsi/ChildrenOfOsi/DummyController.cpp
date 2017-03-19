#include "stdafx.h"
#include "DummyController.h"


DummyController::DummyController(MessageLog* _mLog, TaskBuffer* _tBuffer)
				: Manager(_mLog,_tBuffer)
{ 
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("DummyController Objected Constructed");
	//////////////////////////////////////
}


DummyController::~DummyController()
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("DummyController Objected Destroyed");
	//////////////////////////////////////
}

void DummyController::register_manager()
{
	//THIS IS WHAT YOU EDIT
	//////////////////////////////////////
	tBuffer->add_to_table("DUM", this);
	//////////////////////////////////////
}

void DummyController::execute_task(Task* current_task)
{	
	if (current_task->name == "Move_Up") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = move_up();
		//////////////////////////////////////
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else{
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
int DummyController::move_up()
{
	////std:://cout << "PhyM:Move Up" << std::endl;
	return 0;
}

int DummyController::move_down()
{
	////std:://cout << "PhyM:Move Down" << std::endl;
	return 1;
}
//////////////////////////////////////


