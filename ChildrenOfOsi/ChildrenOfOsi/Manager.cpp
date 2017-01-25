#include "Manager.h"
#include "TaskBuffer.h"

Manager::Manager(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
}


Manager::~Manager()
{
}

void Manager::register_manager() 
{
	LOG("register_manager function not defined");
}

void Manager::send_result(Task* current_task)
{
	tBuffer->push(current_task);
}

void Manager::createTask(std::string task_name, std::string type)
{
	std::string task_status = "PASSED";
	Task* new_task = new Task(task_name, task_status,type);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void  Manager::execute_task(Task* current_task) 
{
	LOG("Execute Task");
}


