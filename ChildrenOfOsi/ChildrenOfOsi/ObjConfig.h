#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"


class ObjConfig
{
public:
	ObjConfig();
	~ObjConfig();

	static void import_config(vector<WorldObj*>* recVec);
	static void set_world_obj(vector<WorldObj*>* recVec, float x, float y, float width, float hight,
		std::string name, std::string tex_file, int frame_num);
};

