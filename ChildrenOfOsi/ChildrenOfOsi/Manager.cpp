#include "stdafx.h"
#include "Manager.h"
#include "TaskBuffer.h"

Manager::Manager(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
}


Manager::~Manager()
{
}

void Manager::register_manager() 
{
	LOG("register_manager function not defined");
}

void Manager::send_result(Task* current_task)
{
	tBuffer->push(current_task);
}

void Manager::createTask(std::string task_name, std::string type)
{
	std::string task_status = "PASSED";
	Task* new_task = new Task(task_name, task_status,type);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void Manager::createTaskWithObj(std::string task_name, std::string type, WorldObj* obj)
{
	std::string task_status = "PASSED";
	Task* new_task = new Task(task_name, task_status, type, obj);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void Manager::createTaskWithObjAndNum(std::string task_name, std::string type, WorldObj* obj, int num)
{
	std::string task_status = "PASSED";
	Task* new_task = new Task(task_name, task_status, type, obj,num);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void Manager::createTaskWithParams(std::string task_name, std::string type, std::string key, float x, float y, bool col) {
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, key, x, y, col);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}
void Manager::createTaskForAudio(std::string _name, std::string _type, char* _source, char* _target, RegionState::soundType _soundType) {
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(_name, task_status, _type, _source, _target,_soundType);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}
void  Manager::execute_task(Task* current_task) 
{
	LOG("Execute Task");
}


