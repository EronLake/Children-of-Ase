#pragma once
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "Manager.h"

//class Manager;

class TaskBuffer
{
private:
	std::priority_queue<Task*> queue_buffer;
	
public:
	TaskBuffer();
	~TaskBuffer();
	void run(MessageLog* mLog, std::unordered_map<std::string, Manager*> mTable);
	void assignTask(Task* current_task, MessageLog* mLog, 
					std::unordered_map<std::string, Manager*> mTable);
	void printBuffer();//////////////////////////NOT IMPLEMENTED
	bool isEmpty();
	void empty();
	void push(Task* new_task);
	Task* pop();
};




