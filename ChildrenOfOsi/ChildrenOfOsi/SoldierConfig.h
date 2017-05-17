#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "MemoryHelper.h"
#include "Containers.h"
#include "ChildrenOfOsi.h"
#include "AIController.h"
#include "ActionConfig.h"
#include "ObjConfig.h"
#include "Texture.h"
#include "AssetInfo.h"

class SoldierConfig
{
public:
	SoldierConfig();
	~SoldierConfig();

	static void import_config(vector<WorldObj*>* recVec, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_soldier(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
		float hight, std::string name, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health, int max_stamina,
		int sol_num);
	//static void init_hero_planner(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, int hero_id);
	static void init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*,
								pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int sol_num);
	static void init_attacks(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, 
								pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int sol_num);
	//static void set_hero_sprites();
};

