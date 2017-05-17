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
		std::string name, std::string tex_file, int frame_num, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int region);
	static void make_stuff(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, int region);
	static unordered_map<Texture*, pair<string, int>> textureMap;
	static vector<Texture*> standard_con;
	static vector<Texture*> oasis_con;
	static vector<Texture*> jungle_con;
	static vector<Texture*> mountain_con;
	static vector<Texture*> marsh_con;
	static constexpr int STANDARD = 0;
	static constexpr int OASIS = 1;
	static constexpr int JUNGLE = 2;
	static constexpr int MOUNTAIN = 3;
	static constexpr int OGUNREG = 4;
	
};

