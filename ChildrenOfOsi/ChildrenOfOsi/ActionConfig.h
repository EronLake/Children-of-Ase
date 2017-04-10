#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"
#include "Actionpool.h"

class ActionConfig
{
public:
	ActionConfig();
	~ActionConfig();

	static void import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner);
	static void set_action_obj(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, Hero* owner,
								Hero* receiver, float utility, float why, std::string type, std::string name, std::string exe_name,
								int a, int k, int h, int p, int r, int e, int g);


};

