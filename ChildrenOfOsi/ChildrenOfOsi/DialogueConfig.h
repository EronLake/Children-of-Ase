#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"


class DialogueConfig
{
public:
	DialogueConfig();
	~DialogueConfig();

	static void import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_conv_point(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string icon, std::string temp, std::string name, std::vector<int> personality_vals,std::string corresponding_conv_point, std::vector<int> relationship_vals, std::string topic, std::string hero_reply);
	static void import_conditions(Json::Value::iterator itr, std::string name);
	static void import_post_conditions(Json::Value::iterator itr, std::string name, std::string which_post);

};

