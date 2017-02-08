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
	if (objToUpdate == nullptr) {
		LOG("TASK IS MADE, BUT OBJ IS ALREADY A NULLPTR");
	}
	LOG("Task Object W/WOBJ Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, float x, float y, bool col)
{
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;

	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = 0;

	LOG("Task Object W/WOBJ&PARAM Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, float x, float y, bool col, int d)
{
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;

	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = d;

	LOG("Task Object W/WOBJ&MOREPARAM Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, WorldObj* _objToUpdate, float x, float y, bool col) {
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;

	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = 0;

	LOG("Task Object W/WOBJ&EVENMOREPARAM Constructed");
}

/*Task::Task(std::string _name, std::string _status, std::string _type, WorldObj* _objToUpdate, float x, float y, bool col, int d) {
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;

	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = d;

	LOG("Task Object W/WOBJ Constructed");
}*/



Task::~Task()
{
	LOG("Task Objected Destroyed");
}

void Task::updateStatus(std::string new_status)
{
	status = new_status;
}

Task* Task::clone_task()
{
	//dupliacates all of the attibutes of original task
	Task* duplicate_task = new Task(name,
									status,
									type,
									objToUpdate,
		                            arg1,
		                            arg2,
		                            arg3);

	return duplicate_task;
}

