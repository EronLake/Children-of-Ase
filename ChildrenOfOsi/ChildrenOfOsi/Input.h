#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"




class Input
{
private:
	MessageLog* mLog;
	TaskBuffer* tBuffer;
	WorldObj* player;

public:
	Input(MessageLog* _mLog, TaskBuffer* _tBuffer);
	Input(MessageLog* _mLog, TaskBuffer* _tBuffer, WorldObj* _player);
	~Input();

	void InputCheck();

	void createTask(std::string task_name, std::string type);
	void createTaskWithObj(std::string task_name, std::string type, WorldObj* _objToUpdate);
};

