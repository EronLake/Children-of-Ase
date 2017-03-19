#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"

class ActionConfig
{
public:
	ActionConfig();
	~ActionConfig();

	static void import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_action_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, int owner,
								int receiver, int doer, float utility, float why,std::string name, std::string exe_name);


};

