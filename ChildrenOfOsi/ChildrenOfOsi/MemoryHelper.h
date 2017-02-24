#pragma once
#include "common.h"
#include "MemNode.h"
#include "MemoryPool.h"
#include "memManager.h"
#include "Containers.h"

class MemoryHelper
{
public:

	int store_hero(std::string key, float x, float y, bool col);
	int store_soldier(std::string key, float x, float y, bool col);
	int store_projectile(std::string key, float x, float y, bool col);
	int store_spl_soldier(std::string key, float x, float y, bool col);
	int store_livingObj(std::string key, float x, float y, bool col);
	int store_worldObj(std::string key, float x, float y, bool col);
	int store_npc(std::string key, float x, float y, bool col);
	int store_texture(std::string key, float x, float y, bool col);

	MemoryHelper::MemoryHelper();
	MemoryHelper::~MemoryHelper();

	//------------------------------------
	//these functions are for initializing the memory pool
	MemNode* init_pool(MemoryPool *p, size_t bsize);
	size_t get_free_pool_size(MemoryPool* p);
	void destroy_pool(MemoryPool* p);
	MemoryPool* create_pool(size_t sizeInBytes);
	void destroy_MemNode_list(MemNode* head_ptr);
	MemNode* make_Available(MemNode* head_ptr, MemoryPool* p, size_t node_number);
	void* find_available_block(MemNode* head_ptr);

};

