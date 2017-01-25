#include "common.h"
#include "WorldObj.h"
#pragma once

class Task
{

public:

	std::string name;
	std::string status;
	std::string type;
	short timestamp;

	Task(std::string name, std::string status, std::string _type);
	~Task();

	void updateStatus(std::string new_status);


};

