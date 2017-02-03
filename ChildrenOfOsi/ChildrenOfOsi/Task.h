#include "stdafx.h"
#include "common.h"
#include "WorldObj.h"
#pragma once

class Task
{

public:

	WorldObj* objToUpdate;
	std::string name;
	std::string status;
	std::string type;
	short timestamp;

	Task(std::string name, std::string status, std::string _type);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate);
	~Task();

	void updateStatus(std::string new_status);
	Task* clone_task();


};

