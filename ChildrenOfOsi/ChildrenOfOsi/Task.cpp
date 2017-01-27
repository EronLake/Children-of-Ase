#include "stdafx.h"
#include "Task.h"


Task::Task(std::string _name, std::string _status, std::string _type)
{
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;
	LOG("Task Objected Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, WorldObj * _objToUpdate)
{
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;
	objToUpdate = _objToUpdate;
	LOG("Task Object W/WOBJ Constructed");
}

Task::~Task()
{
	LOG("Task Objected Destroyed");
}

void Task::updateStatus(std::string new_status)
{
	status = new_status;
}

