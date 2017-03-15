#pragma once
#include "common.h"
#include "MemNode.h"
#include "MemoryPool.h"
#include "memManager.h"
#include "Containers.h"
#include "CheckClass.h"

class MemoryHelper
{
public:

	int store_hero(std::string key, float x, float y, bool col);
	int store_soldier(std::string key, float x, float y, bool col);
	int store_Attack(std::string key, float x, float y, bool col);
	int new_Attack(WorldObj* obj, int num);
	int store_spl_soldier(std::string key, float x, float y, bool col);
	int store_livingObj(std::string key, float x, float y, bool col);
	int store_worldObj(std::string key, float x, float y, bool col);
	int store_npc(std::string key, float x, float y, bool col);
	int store_texture(std::string key, float x, float y, bool col);
	int del_Attack(std::string key, float x, float y, bool col);

	int store_memory(std::string key, int hero_name, int t, int frames, vector<NPC*> p, string cat = "", string cont = "", string where = "", int why = -1, int when = -1);
	int store_action(std::string key);

	MemoryHelper::MemoryHelper();
	MemoryHelper::~MemoryHelper();

	//------------------------------------
	//these functions are for initializing the memory pool
	MemNode* init_pool(MemoryPool *p, size_t bsize);
	size_t get_free_pool_size(MemoryPool* p);
	void destroy_pool(MemoryPool* p);
	MemoryPool* create_pool(size_t sizeInBytes);
	void destroy_MemNode_list(MemNode* head_ptr);
	MemNode* make_Available(MemNode* head_ptr, MemoryPool* p, std::string key);
	void* find_available_block(MemNode* head_ptr, std::string str);

};

