
#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "Pool.h"


class memManager : public Manager
{
public:
	memManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~memManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};

static MemoryPool* hero_pool = nullptr;
static MemNode* hero_head = nullptr;

static MemoryPool* livingObj_pool = nullptr;
static MemNode* livingObj_head = nullptr;

static MemoryPool* projectile_pool = nullptr;
static MemNode* projectile_head = nullptr;

static MemoryPool* soldier_pool = nullptr;
static MemNode* soldier_head = nullptr;

static MemoryPool* spl_soldier_pool = nullptr;
static MemNode* spl_soldier_head = nullptr;

static MemoryPool* worldObj_pool = nullptr;
static MemNode* worldObj_head = nullptr;

static MemoryPool* npc_pool = nullptr;
static MemNode* npc_head = nullptr;

void store_hero(float x, float y, bool col);
void store_soldier(float x, float y, bool col);
void store_projectile(float x, float y, bool col, int d);
void store_spl_soldier(float x, float y, bool col);
void store_livingObj(float x, float y, bool col);
void store_worldObj(float x, float y, bool col);
void store_npc(float x, float y, bool col);

