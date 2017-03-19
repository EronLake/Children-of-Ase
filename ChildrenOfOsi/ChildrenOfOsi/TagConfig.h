#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"


class TagConfig
{
public:
	TagConfig();
	~TagConfig();

	static void import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_tag(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, std::vector<std::string> topicVec);

};

