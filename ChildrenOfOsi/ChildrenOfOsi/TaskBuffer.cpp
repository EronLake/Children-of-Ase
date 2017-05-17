#include "stdafx.h"
#include "TaskBuffer.h"
#include <exception>
struct empty_stack : std::exception
{
	const char* what() const throw() {
		return "Empty Stack Exception";
	}
};

std::mutex mux_2;
std::mutex mux_3;

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
		assignTask(0, current_task);
	}
	//LOG("TaskBuffer Stoping");
}


//------------------------------------------------------
void TaskBuffer::assignTask(int id, Task* current_task)
{
	//cout << "assign task is being called" << endl;
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
				LOG("TASK DUPLICATED");
				Task* duplicate_task = current_task->clone_task();
				LOG("PRIOR TO EXECUTING THE DUP TASK");
				(*itr)->execute_task(duplicate_task);
			}
			//delete current_task;
		}
		else
		{
			LOG("Error: Task type '" << current_task->type << "' does not exist"); //perror?
		}
	}
	else if (current_task->status == "COMPLETED" ||
		current_task->status == "FAILED")
	{
		//confirm task was completed or failed in MessageLog
		mLog->logMessage(current_task);
		//delete current_task;
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
	std::lock_guard<std::mutex> guard(mux_2);
	queue_buffer.push_front(std::move(new_task));
	mLog->logMessage(new_task);
}
void TaskBuffer::push_physics(Task * new_task)
{
	std::lock_guard<std::mutex> guard(mux_3);
	physics_buffer.push_front(std::move(new_task));
	mLog->logMessage(new_task);

}
//------------------------------------------------------

//------------------------------------------------------
//removes and returns top of the TaskBuffer
Task* TaskBuffer::pop()
{
	std::lock_guard<std::mutex> guard(mux_2);
	if (queue_buffer.empty()) throw empty_stack();
	Task* const top_task = std::move(queue_buffer.front());
	queue_buffer.pop_front();
	return top_task;
}
Task * TaskBuffer::pop_physics()
{
	std::lock_guard<std::mutex> guard(mux_3);
	if (physics_buffer.empty()) throw empty_stack();
	Task* const top_task = std::move(physics_buffer.front());
	physics_buffer.pop_front();
	return top_task;
}
//------------------------------------------------------

//------------------------------------------------------
//checks if the TaskBuffer is empty
bool TaskBuffer::isEmpty() const
{
	std::lock_guard<std::mutex> guard(mux_2);
	return queue_buffer.empty(); 
}
bool TaskBuffer::physics_buffer_isEmpty() const
{
	std::lock_guard<std::mutex> guard(mux_3);
	return physics_buffer.empty();
}
//------------------------------------------------------

//------------------------------------------------------
//empties the TaskBuffer
void TaskBuffer::empty()
{
	if (!queue_buffer.empty()) {
		queue_buffer = std::deque<Task*>();
	}
}

void TaskBuffer::physics_buffer_empty()
{
	if (!physics_buffer.empty()) {
		physics_buffer = std::deque<Task*>();
	}
}

void TaskBuffer::add_to_table(std::string type, Manager* manager)
{
	mTable[type].push_back(manager);
}

//------------------------------------------------------

