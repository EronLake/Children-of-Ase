#include "stdafx.h"
#include "Task.h"


Task::Task(std::string _name, std::string _status, std::string _type, char* _source, char* _target)
{
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;

	source = _source; //optional arguments for audio
	target = _target;
	LOG("Task Objected Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, WorldObj * _objToUpdate)
{
	name = _name;
	type = _type;

	status = _status;
	objToUpdate = _objToUpdate;
	if (objToUpdate == nullptr) {
		LOG("TASK IS MADE, BUT OBJ IS ALREADY A NULLPTR");
	}
	LOG("Task Object W/WOBJ Constructed");
}


Task::Task(std::string _name, std::string _status, std::string _type, WorldObj * _objToUpdate, int num)
{
	name = _name;
	type = _type;

	status = _status;
	objToUpdate = _objToUpdate;
	arg4 = num;

	if (objToUpdate == nullptr) {
		LOG("TASK IS MADE, BUT OBJ IS ALREADY A NULLPTR");
	}
	LOG("Task Object W/WOBJ Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, std::string _key, float x, float y, bool col)
{
	name = _name;
	type = _type;

	status = _status;

	key = _key;
	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = 0;

	LOG("Task Object W/WOBJ&PARAM Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, std::string _key, float x, float y, bool col, int d)
{
	name = _name;
	type = _type;

	status = _status;

	key = _key;
	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = d;

	LOG("Task Object W/WOBJ&MOREPARAM Constructed");
}


Task::Task(std::string _name, std::string _status, std::string _type, std::string _key, int d, WorldObj* _objToUpdate,
			float x, float y, bool col) {
	name = _name;
	type = _type;

	status = _status;
	objToUpdate = _objToUpdate;

	key = _key;
	arg1 = x;
	arg2 = y;
	arg3 = col;
	arg4 = 0;

	LOG("Task Object W/WOBJ&EVENMOREPARAM Constructed");
}


Task::Task(std::string _name, std::string _status, std::string _type, std::string _key, int hero_name, int _mem_type, int _frames, 
			vector<NPC*> _people, std::string _cat, std::string _cont, std::string _where, int _why, int _when)
{
	name = _name;
	type = _type;

	status = _status;

	key = _key;
	arg4 = hero_name;
	mem_type = _mem_type;
	frames = _frames;
	people = _people;
	cat = _cat;
	cont = _cont;
	where = _where;
	why = _why;
	when = _when;

	LOG("Task Object W/WOBJ&MEM Constructed");
}


Task::Task(std::string _name, std::string _status, std::string _type, std::string _key, int _utility, int _why, Hero* _owner,
	Hero* _receiver, Hero* _doer, std::string _exe_name)
{
	name = _name;
	type = _type;

	status = _status;

	key = _key;
	arg1 = 0.0;
	arg2 = 0.0;
	arg3 = false;
	arg4 = _utility;
	why = _why;

	cat = _exe_name;
	owner = _owner;
	receiver = _receiver;
	doer = _doer;

	LOG("Task Object W/WOBJ&ACT Constructed");
}

Task::Task(std::string _name, std::string _status, std::string _type, std::string _topic, std::string _temp, std::string _key)
{
	name = _name;
	type = _type;

	status = _status;

	my_key = _key;
	topic = _topic;
	temp = _temp;

}

Task::Task(std::string _name, std::string _status, std::string _type, std::string _key)
{
	name = _name;
	type = _type;
	status = _status;
	my_key = _key;

}

/*Task::Task(std::string _name, std::string _status, std::string _type, WorldObj* _objToUpdate, float x, float y, bool col, int d) {
	name = _name;
	type = _type;
	//[buffer,manager,class]
	//fucntion_name
	//object

	status = _status;
	objToUpdate = _objToUpdate;

	key = _key;
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
	//duplicates all of the attibutes of original task
	Task* duplicate_task = new Task(name,status,type);
	duplicate_task->key = key;
	duplicate_task->arg1 = arg1;
	duplicate_task->arg2 = arg2;
	duplicate_task->arg3 = arg3;
	duplicate_task->arg4 = arg4;
	duplicate_task->objToUpdate = objToUpdate;
	duplicate_task->mem_type = mem_type;
	duplicate_task->frames = frames;
	duplicate_task->people = people;
	duplicate_task->cat = cat;
	duplicate_task->cont = cont;
	duplicate_task->where = where; 
	duplicate_task->why = why; 
	duplicate_task->when = when;
	duplicate_task->owner = owner;
	duplicate_task->receiver = receiver;
	duplicate_task->doer = doer;
	duplicate_task->topic = topic;
	duplicate_task->temp = temp;
	duplicate_task->my_key = my_key;
	duplicate_task->topicVec = topicVec;
	duplicate_task->source = source;
	duplicate_task->target = target;
		
	return duplicate_task;
}

