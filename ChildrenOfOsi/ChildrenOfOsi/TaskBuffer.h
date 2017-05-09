#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "Manager.h"
#include "ThreadManager.h"
//#include "PhysicsManager.h"

//class Manager;

class TaskBuffer
{
private:
	
	MessageLog* mLog;
	std::unordered_map<std::string, std::vector<Manager*>> mTable;

public:
	TaskBuffer(MessageLog* _mLog);
	~TaskBuffer();
	void run();
	void pre_run();
	void assignTask(bool for_prerun, Task* current_task);
	void printBuffer();//////////////////////////NOT IMPLEMENTED
	bool isEmpty() const;
	bool physics_buffer_isEmpty() const;
	void empty();
	void physics_buffer_empty();
	void push(Task* new_task);
	void push_physics(Task* new_task);
	Task* pop();
	Task* pop_physics();
	void test() { return; }
	void add_to_table(std::string type, Manager* manager);
	std::deque<Task*> queue_buffer;
	std::deque<Task*> physics_buffer;
};




