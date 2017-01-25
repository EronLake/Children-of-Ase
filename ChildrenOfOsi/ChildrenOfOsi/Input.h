#pragma once
#include "common.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"




class Input
{
private:
	MessageLog* mLog;
	TaskBuffer* tBuffer;

public:
	Input(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~Input();

	void InputCheck();

	void createTask(std::string task_name, std::string type);
};

