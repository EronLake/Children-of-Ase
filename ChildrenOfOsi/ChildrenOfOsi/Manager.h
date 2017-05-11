#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"


class TaskBuffer;

class Manager
{
protected:
	MessageLog* mLog;
	TaskBuffer* tBuffer;
public:
	Manager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~Manager();

	virtual void register_manager();

	void send_result(Task* current_task);

	void createTask(std::string task_name, std::string type);

	void createTaskWithObj(std::string task_name, std::string type, WorldObj* obj);

	void createTaskWithObjAndNum(std::string task_name, std::string type, WorldObj* obj, int num);

	void createTaskWithParams(std::string task_name, std::string type, std::string key, float x, float y, bool col);

	void createTaskForAudio(std::string _name, std::string _type, char* _source = nullptr, char* _target = nullptr, RegionState::soundType _soundType = RegionState::soundType::null_type);

	virtual void execute_task(Task* current_task);
};


