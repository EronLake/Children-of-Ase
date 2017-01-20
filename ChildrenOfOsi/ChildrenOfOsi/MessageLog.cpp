#include "MessageLog.h"


MessageLog::MessageLog()
{
	LOG("MessageLog Objected Constructed");
}


MessageLog::~MessageLog()
{
	if (MessageLog::isEmpty() == false) {
		MessageLog::empty();
	}
	LOG("MessageLog Objected Destroyed");
}

void MessageLog::logMessage(Task* task_passed) 
{
	std::string message = task_passed->name + 
					":" + task_passed->status;
	queue_log.push("MESSAGE-LOG:" + message);
	std::cout << "MESSAGE-LOG:" << message << std::endl;
}

//------------------------------------------------------
//checks if the TaskBuffer is empty
bool MessageLog::isEmpty()
{
	return (queue_log.size() == 0);
}
//------------------------------------------------------

//------------------------------------------------------
//empties the TaskBuffer
void MessageLog::empty()
{
	queue_log.empty();
}
//------------------------------------------------------

