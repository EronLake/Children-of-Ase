#include "Manager.h"
#include "TaskBuffer.h"

Manager::Manager()
{
	LOG("TaskBuffer Objected Constructed");
}


Manager::~Manager()
{
	LOG("TaskBuffer Objected Destroyed");
}

void Manager::send_result(Task* current_task, TaskBuffer* tBuffer)
{
	tBuffer->push(current_task);
}

void Manager::createTask(TaskBuffer* tBuffer, MessageLog* mLog,
	std::string task_name)
{
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void  Manager::execute_task(Task* current_task, MessageLog* mLog,
							TaskBuffer* tbuffer) 
{
	LOG("TaskBuffer Objected Constructed");
}


