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
	std::string key;
	float arg1;
	float arg2;
	bool arg3;
	int arg4;
	short timestamp;

	Task(std::string name, std::string status, std::string _type);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, int num);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col, int d);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, std::string key, float x, float y, bool col);
	//Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, std::string key,float x, float y, bool col, int d);
	~Task();

	void updateStatus(std::string new_status);
	Task* clone_task();


};

