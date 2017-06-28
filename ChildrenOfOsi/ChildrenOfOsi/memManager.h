#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "MemoryPool.h"
#include "MemNode.h"
#include "Memory.h"
#include "Action.h"


class MemoryHelper;

class memManager : public Manager
{
private:

	typedef int (MemoryHelper::*fn_ptr)(std::string,float, float, bool);
	typedef int (MemoryHelper::*fn_ptr2)(WorldObj* obj, int num);
	typedef int (MemoryHelper::*fn_ptr3)(std::string key, int hero_name, int mem_type, int frames, vector<NPC*> people, string cat, string cont, string where, int why, int when);
	typedef int (MemoryHelper::*fn_ptr4)(std::string key, int utility, int why, Hero* owner, Hero* receiver, Hero* doer, std::string exe_name);
	typedef int (MemoryHelper::*fn_ptr5)(std::vector<std::string> topicVec, std::string key);
	typedef std::map<std::string, fn_ptr> functionMapper;
	typedef std::map<std::string, fn_ptr2> function2Mapper;
	typedef std::map<std::string, fn_ptr3> HeroMemfunctionMapper;
	typedef std::map<std::string, fn_ptr4> HeroActfunctionMapper;
	typedef std::map<std::string, fn_ptr5> tagMemMapper;


	functionMapper task_map;
	function2Mapper task_map2;
	HeroMemfunctionMapper task_map3;
	HeroActfunctionMapper task_map4;
	tagMemMapper task_map5;

	MemoryHelper* memHelper;

public:	

	static MemoryPool* hero_pool;
	static MemNode* hero_head;

	static MemoryPool* livingObj_pool;
	static MemNode* livingObj_head;

	static MemoryPool* Attack_pool;
	static MemNode* Attack_head;

	static MemoryPool* soldier_pool;
	static MemNode* soldier_head;

	static MemoryPool* spl_soldier_pool;
	static MemNode* spl_soldier_head;

	static MemoryPool* worldObj_pool;
	static MemNode* worldObj_head;

	static MemoryPool* npc_pool;
	static MemNode* npc_head;

	static MemoryPool* texture_pool;
	static MemNode* texture_head;

	static MemoryPool* oya_memory_pool;
	static MemNode* oya_memory_head;

	static MemoryPool* yemoja_memory_pool;
	static MemNode* yemoja_memory_head;

	static MemoryPool* oshosi_memory_pool;
	static MemNode* oshosi_memory_head;

	static MemoryPool* ogun_memory_pool;
	static MemNode* ogun_memory_head;

	static MemoryPool* shango_memory_pool;
	static MemNode* shango_memory_head;

	static MemoryPool* action_pool;
	static MemNode* action_head;

	static MemoryPool* tag_pool;
	static MemNode* tag_head;

	static MemoryPool* conv_point_pool;
	static MemNode* conv_point_head;

	//for tasks in the task buffer
	static MemoryPool* task_pool;
	static MemNode* task_head;

	memManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~memManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




