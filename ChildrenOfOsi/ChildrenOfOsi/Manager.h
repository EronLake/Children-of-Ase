#pragma once
#include "common.h"
#include "Task.h"
#include "MessageLog.h"


class TaskBuffer;

class Manager
{
public:
	Manager();
	~Manager();

	void send_result(Task* current_task, TaskBuffer* tBuffer);

	void createTask(TaskBuffer* tBuffer, MessageLog* mLog,
		std::string task_name);

	virtual void execute_task(Task* current_task, MessageLog* mLog,
		TaskBuffer* tBuffer);
};


