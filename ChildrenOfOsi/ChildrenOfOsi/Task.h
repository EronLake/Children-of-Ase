#include "stdafx.h"
#include "common.h"
#include "WorldObj.h"
#include "NPC.h"
#pragma once

class Task
{

public:

	WorldObj* objToUpdate;
	std::string name;
	std::string status;
	std::string type;
	std::string key;
	float arg1 = 0.0;
	float arg2 = 0.0;
	bool arg3 = false;
	int arg4 = 0;

	int mem_type = 0;
	int frames = 0; 
	vector<NPC*> people; 
	std::string cat = "empty";
	std::string cont = "empty";
	std::string where = "empty";
	int why = 0;
	int when = 0;

	short timestamp;

	Task(std::string name, std::string status, std::string _type);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, int num);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col, int d);
	
	Task(std::string name, std::string status, std::string _type, std::string key, int d, WorldObj* _objToUpdate, float x, float y, bool col);
	//for adding hero memories
	Task(std::string name, std::string status, std::string _type, std::string key,int hero_name, int mem_type, int frames, 
			vector<NPC*> p, std::string cat, std::string cont, std::string where, int why, int when);
	//Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, std::string key,float x, float y, bool col, int d);
	~Task();

	void updateStatus(std::string new_status);
	Task* clone_task();


};

