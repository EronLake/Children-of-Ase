#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"


class ObjConfig
{
public:
	ObjConfig();
	~ObjConfig();

	static void import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_world_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width, float hight,
		std::string name, std::string tex_file, int frame_num, float bodyx1, float bodyx2, float bodyy1, float bodyy2);

};

