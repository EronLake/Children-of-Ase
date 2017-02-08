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

	typedef int (MemoryHelper::*fn_ptr)(float, float, bool);
	typedef std::map<std::string, fn_ptr> functionMapper;

	functionMapper task_map;

	MemoryHelper* memHelper;

public:

	static MemoryPool* hero_pool;// = nullptr;
	static MemNode* hero_head;// = nullptr;

	static MemoryPool* livingObj_pool;// = nullptr;
	static MemNode* livingObj_head;// = nullptr;

	static MemoryPool* projectile_pool;// = nullptr;
	static MemNode* projectile_head;// = nullptr;

	static MemoryPool* soldier_pool;// = nullptr;
	static MemNode* soldier_head;// = nullptr;

	static MemoryPool* spl_soldier_pool;// = nullptr;
	static MemNode* spl_soldier_head;// = nullptr;

	static MemoryPool* worldObj_pool;// = nullptr;
	static MemNode* worldObj_head;// = nullptr;

	static MemoryPool* npc_pool;// = nullptr;
	static MemNode* npc_head;// = nullptr;

	memManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~memManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




