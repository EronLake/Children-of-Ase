#pragma once
#include "common.h"
#include "Task.h"
#include "MessageLog.h"


class TaskBuffer;

class Manager
{
protected:
	MessageLog* mLog;
	TaskBuffer* tBuffer;
public:
	Manager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~Manager();

	virtual void register_manager();

	void send_result(Task* current_task);

	void createTask(std::string task_name, std::string type);

	virtual void execute_task(Task* current_task);
};


