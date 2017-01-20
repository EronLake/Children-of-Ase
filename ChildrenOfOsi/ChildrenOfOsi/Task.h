#include "common.h"
#pragma once

class Task
{

public:

	std::string name;
	std::string status;
	short timestamp;

	Task(std::string name, std::string status);
	~Task();

	void updateStatus(std::string new_status);


};

