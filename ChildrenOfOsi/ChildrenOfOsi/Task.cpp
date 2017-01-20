#include "Task.h"


Task::Task(std::string _name,std::string _status)
{
	name = _name;
	//manager_name
	//fucntion_name
	//object

	status = _status;
	LOG("Task Objected Constructed");
}

Task::~Task()
{
	LOG("Task Objected Destroyed");
}

void Task::updateStatus(std::string new_status)
{
	status = new_status;
}

