#include "stdafx.h"
#include "common.h"
#include "WorldObj.h"
#include "NPC.h"
#include "Hero.h"
#include "RegionState.h"
#pragma once

class Task
{

public:

	WorldObj* objToUpdate;
	std::string name;
	std::string status;
	std::string type;
	std::string key;
	std::vector<std::string> topicVec;
	std::string topic;
	std::string temp;
	std::string my_key;
	float arg1 = 0.0;
	float arg2 = 0.0;
	bool arg3 = false;
	int arg4 = 0;
	char* source = nullptr;
	char* target = nullptr;
	RegionState::soundType soundType = RegionState::soundType::null_type;
	int mem_type = 0;
	int frames = 0; 
	vector<NPC*> people; 
	std::string cat = "empty";
	std::string cont = "empty";
	std::string where = "empty";
	int why = 0;
	int when = 0;

	Hero* owner = NULL;
	Hero* receiver = NULL;
	Hero* doer = NULL;

	short timestamp;

	Task(std::string name, std::string status, std::string _type, char* _source = nullptr, char* _target = nullptr, RegionState::soundType _soundType = RegionState::soundType::null_type);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate);
	Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, int num);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col);
	Task(std::string _name, std::string _status, std::string _type, std::string key, float x, float y, bool col, int d);
	
	Task(std::string name, std::string status, std::string _type, std::string key, int d, WorldObj* _objToUpdate, float x, float y, bool col);
	//for adding hero memories
	Task(std::string name, std::string status, std::string _type, std::string key,int hero_name, int mem_type, int frames, 
			vector<NPC*> p, std::string cat, std::string cont, std::string where, int why, int when);
	//for adding actions
	Task(std::string name, std::string status, std::string _type, std::string key, int utility, int why, Hero* owner, Hero* receiver,
		Hero* doer, std::string exe_name);
	//for conversation points
	Task(std::string _name, std::string _status, std::string _type, std::string topic, std::string temp, std::string key);
	//for tags
	Task(std::string _name, std::string _status, std::string _type, std::string key);
	//Task(std::string name, std::string status, std::string _type, WorldObj* _objToUpdate, std::string key,float x, float y, bool col, int d);
	
	~Task();

	void updateStatus(std::string new_status);
	Task* clone_task();


};

