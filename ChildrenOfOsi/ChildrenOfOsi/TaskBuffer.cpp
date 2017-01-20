#include "TaskBuffer.h"

//------------------------------------------------------
TaskBuffer::TaskBuffer()
{
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


void TaskBuffer::run(MessageLog* mLog, std::unordered_map<std::string, Manager*> mTable)
{
	//LOG("TaskBuffer Running");
	if (isEmpty() == false) {
		Task* current_task = (pop());
		assignTask(current_task, mLog, mTable);
	}
	//LOG("TaskBuffer Stoping");
}


//------------------------------------------------------
void TaskBuffer::assignTask(Task* current_task,MessageLog* mLog,
							std::unordered_map<std::string, Manager*> mTable)
{
	if (current_task->status == "CREATED" ||
		current_task->status == "WORKING")
	{
		//confirm task was assigned and is working in MessageLog
		current_task->updateStatus("WORKING");
		if (current_task->name == "MemM:Mk Obj")
		{
			//call Memory Manager Function to handle task
			mLog->logMessage(current_task);
			std::cout << "MemM:Mk Obj assigned" << std::endl;

		}
		else if (current_task->name == "MemM:Obj Freed")
		{
			//call Memory Manager Function to handle task
			mLog->logMessage(current_task);
			std::cout << "MemM:Obj Freed" << std::endl;
		}
		else if (current_task->name == "PhyM:Move Up" ||
				current_task->name == "PhyM:Move Down")
		{
			//call Memory Manager Function to handle task
			mLog->logMessage(current_task);
			mTable.find("DumM")->second->execute_task(current_task, 
						mLog,this);
		}
		else
		{
			LOG("Error: Task name does not exist"); //perror?
			return;
		}
	}
	else if (current_task->status == "COMPLETED" ||
			 current_task->status == "FAILED")
	{
		//confirm task was completed or failed in MessageLog
		mLog->logMessage(current_task);
		delete current_task;
	}else
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


//------------------------------------------------------

