#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "MemoryPool.h"
#include "MemNode.h"

class MemoryHelper;

class memManager : public Manager
{
private:

	typedef int (MemoryHelper::*fn_ptr)(std::string,float, float, bool);
	typedef std::map<std::string, fn_ptr> functionMapper;

	functionMapper task_map;
	MemoryHelper* memHelper;

public:	

	static MemoryPool* hero_pool;
	static MemNode* hero_head;

	static MemoryPool* livingObj_pool;
	static MemNode* livingObj_head;

	static MemoryPool* projectile_pool;
	static MemNode* projectile_head;

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

	memManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~memManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




