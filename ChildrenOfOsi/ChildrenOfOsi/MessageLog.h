#include "common.h"
#include "Task.h"
#pragma once
class MessageLog
{
private:
	std::queue<std::string> queue_log;
	std::ofstream log_file;
public:
	MessageLog();
	~MessageLog();

	void logMessage(Task* current_task);
	bool isEmpty();
	void empty();
	void push_to_log(std::string message);

};

