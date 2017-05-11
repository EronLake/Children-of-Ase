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

class HeroConfig
{
public:
	HeroConfig();
	~HeroConfig();

	static void import_config(vector<WorldObj*>* recVec, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
	static void set_hero(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
		float hight, std::string name, int hero_id, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health, int max_stamina,
		int a, int k, int h, int p, int r, int e, int g);
	static void init_hero_planner(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, int hero_id);
	static void init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int hero_id);
	static void set_hero_sprites();
};

