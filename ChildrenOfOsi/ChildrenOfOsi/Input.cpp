#include "Input.h"
#include <conio.h>

Input::Input(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	LOG("Input Objected Constructed");
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
			createTask("Move_Up", "MOVE");
		}
		else if (key == 'a')
		{
			createTask("Move_Left", "MOVE");
		}
		else if (key == 's')
		{
			createTask("Move_Down", "MOVE");
		}
		else if (key == 'd')
		{
			createTask("Move_Right", "MOVE");
		}
	}
}

void Input::createTask(std::string task_name, std::string type)
{
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

