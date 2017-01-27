#include "stdafx.h"
#include "Input.h"
#include <conio.h>

Input::Input(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	LOG("Input Objected Constructed");
}

Input::Input(MessageLog * _mLog, TaskBuffer * _tBuffer, WorldObj * _player)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	player = _player;
	LOG("Input Object W/Player Constructed");
}


Input::~Input()
{
	LOG("Input Objected Destroyed");
}

void Input::InputCheck()
{
	int key;
	if (_kbhit())
	{
		key = _getch();

		if (key == 'w')
		{
			//createTask("Move_Up", "MOVE");
			createTaskWithObj("Move_Up", "MOVE", player);
		}
		else if (key == 'a')
		{
			//createTask("Move_Left", "MOVE");
			createTaskWithObj("Move_Left", "MOVE", player);

		}
		else if (key == 's')
		{
			//createTask("Move_Down", "MOVE");
			createTaskWithObj("Move_Down", "MOVE", player);

		}
		else if (key == 'd')
		{
			//createTask("Move_Right", "MOVE");
			createTaskWithObj("Move_Right", "MOVE", player);

		}
	}
}

void Input::createTask(std::string task_name, std::string type)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void Input::createTaskWithObj(std::string task_name, std::string type, WorldObj * _objToUpdate)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, _objToUpdate);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}



