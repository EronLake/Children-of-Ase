#pragma once
#include "common.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"




class Input
{
public:
	Input();
	~Input();

	void InputCheck(TaskBuffer* Tbuffer, MessageLog* Mlog);

	void createTask(TaskBuffer* Tbuffer, MessageLog* Mlog,
		std::string task_name);
};

