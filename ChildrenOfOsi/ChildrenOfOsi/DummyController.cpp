#include "DummyController.h"



DummyController::DummyController()
{
}


DummyController::~DummyController()
{
}

void DummyController::execute_task(Task* current_task, MessageLog* mLog,
								TaskBuffer* tBuffer)
{	
	if (current_task->name == "PhyM:Move Up") {
		int result = move_up();
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else{
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task, tBuffer);
	}
	else if (current_task->name == "PhyM:Move Down") {
		int result = move_down();
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task, tBuffer);
	}
}

int DummyController::move_up()
{
	std::cout << "PhyM:Move Up" << std::endl;
	return 0;
}

int DummyController::move_down()
{
	std::cout << "PhyM:Move Down" << std::endl;
	return 1;
}


