#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "Manager.h"

//class Manager;

class TaskBuffer
{
private:
	std::priority_queue<Task*> queue_buffer;
	MessageLog* mLog;
	std::unordered_map<std::string, std::vector<Manager*>> mTable;

public:
	TaskBuffer(MessageLog* _mLog);
	~TaskBuffer();
	void run();
	void assignTask(Task* current_task);
	void printBuffer();//////////////////////////NOT IMPLEMENTED
	bool isEmpty();
	void empty();
	void push(Task* new_task);
	Task* pop();
	void add_to_table(std::string type, Manager* manager);
};




