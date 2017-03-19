#include "stdafx.h"
#include "MessageLog.h"


MessageLog::MessageLog()
{
	log_file.open("message_log.txt", std::ofstream::out 
					| std::ofstream::trunc);

	LOG("MessageLog Objected Constructed");
}


MessageLog::~MessageLog()
{
	//if (MessageLog::isEmpty() == false) {
	//	MessageLog::empty();
	//}
	log_file.close();
	LOG("MessageLog Objected Destroyed");
}

void MessageLog::logMessage(Task* task_passed) 
{

	std::string message = task_passed->type +
					":"	+ task_passed->name + 
					":" + task_passed->status;

	log_file << "MESSAGE-LOG:" << message << std::endl;
	////std::////cout << "MESSAGE-LOG:" << message << std::endl;
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

void MessageLog::push_to_log(std::string message)
{
	
	
}