#pragma once
#include "common.h"
#include "MemNode.h"
#include "MemoryPool.h"
#include "memManager.h"

class MemoryHelper
{
public:

	int store_hero(float x, float y, bool col);
	int store_soldier(float x, float y, bool col);
	int store_projectile(float x, float y, bool col);
	int store_spl_soldier(float x, float y, bool col);
	int store_livingObj(float x, float y, bool col);
	int store_worldObj(float x, float y, bool col);
	int store_npc(float x, float y, bool col);

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

