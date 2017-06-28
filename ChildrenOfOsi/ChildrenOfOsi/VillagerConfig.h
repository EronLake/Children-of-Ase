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

class VillagerConfig
{
public:
	VillagerConfig();
	~VillagerConfig();

	static void import_config(vector<WorldObj*>* recVec_ptr, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_villager(vector<WorldObj*>* recVec_ptr, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
		float hight, std::string name, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health);
	
	static void init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*,
		pair<string, int>>*textureMap, Json::Value::iterator itr, std::string name);
};

