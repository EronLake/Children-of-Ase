#include "Input.h"
#include <conio.h>

Input::Input()
{
	LOG("Input Objected Constructed");
}


Input::~Input()
{
	LOG("Input Objected Destroyed");
}

void Input::InputCheck(TaskBuffer* tBuffer, MessageLog* mLog)
{
	int key;
	if (_kbhit())
	{
		key = _getch();

		if (key == 'w') 
		{
			createTask(tBuffer, mLog, "PhyM:Move Up");
		}
		else if (key == 's')
		{
			createTask(tBuffer, mLog, "PhyM:Move Down");
		}
			
	}
}

void Input::createTask(TaskBuffer* tBuffer, MessageLog* mLog,
						std::string task_name)
{
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

