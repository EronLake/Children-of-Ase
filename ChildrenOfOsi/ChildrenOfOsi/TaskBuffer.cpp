#include "stdafx.h"
#include "TaskBuffer.h"

//------------------------------------------------------
TaskBuffer::TaskBuffer(MessageLog* _mLog)
{
	mLog = _mLog;
	LOG("TaskBuffer Objected Constructed");
}
//------------------------------------------------------

//------------------------------------------------------
TaskBuffer::~TaskBuffer()
{
	if (TaskBuffer::isEmpty() == false) {
		TaskBuffer::empty();
	}
	LOG("TaskBuffer Objected Destroyed");
}
//------------------------------------------------------


void TaskBuffer::run()
{
	//LOG("TaskBuffer Running");
	while (isEmpty() == false) {
		Task* current_task = (pop());
		assignTask(current_task);
	}
	//LOG("TaskBuffer Stoping");
}


//------------------------------------------------------
void TaskBuffer::assignTask(Task* current_task)
{
	//will a manager ever create a task or simply pass one?
	if (current_task->status == "CREATED" ||
		current_task->status == "PASSED")
	{
		//confirm task was assigned and is working in MessageLog
		current_task->updateStatus("WORKING");
		//switch(current_task->type) {
		//	case('DUM'):
		//	{
		if (mTable.count(current_task->type) != 0)
		{
			//call DummyController Function to handle task
			std::vector<Manager*> type_man_vec = mTable.find(current_task->type)->second;
			mLog->logMessage(current_task);
			for (auto itr = type_man_vec.begin(); itr != type_man_vec.end(); itr++)
			{
				//clone task and send off to manager
				Task* duplicate_task = current_task->clone_task();
				(*itr)->execute_task(duplicate_task);
			}
			delete current_task;
		}
		else
		{
			LOG("Error: Task type does not exist"); //perror?
		}
	}
	else if (current_task->status == "COMPLETED" ||
		current_task->status == "FAILED")
	{
		//confirm task was completed or failed in MessageLog
		mLog->logMessage(current_task);
		delete current_task;
	}
	else
	{
		LOG("not valid status");
	}
}
//------------------------------------------------------

//------------------------------------------------------
void TaskBuffer::printBuffer()//////////////////////////NOT IMPLEMENTED
{
}
//------------------------------------------------------

//------------------------------------------------------
//removes and returns top of the TaskBuffer
void TaskBuffer::push(Task* new_task)
{
	queue_buffer.push(new_task);
}
//------------------------------------------------------

//------------------------------------------------------
//removes and returns top of the TaskBuffer
Task* TaskBuffer::pop()
{
	Task* top_task = queue_buffer.top();
	queue_buffer.pop();
	return top_task;
}
//------------------------------------------------------

//------------------------------------------------------
//checks if the TaskBuffer is empty
bool TaskBuffer::isEmpty()
{
	return (queue_buffer.size() == 0);
}
//------------------------------------------------------

//------------------------------------------------------
//empties the TaskBuffer
void TaskBuffer::empty()
{
	queue_buffer.empty();
}

void TaskBuffer::add_to_table(std::string type, Manager* manager)
{
	mTable[type].push_back(manager);
}

//------------------------------------------------------

