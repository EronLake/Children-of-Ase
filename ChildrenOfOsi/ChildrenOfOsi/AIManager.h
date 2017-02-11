#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "AIHelper.h"

class AIManager : public Manager
{
private:
	AIHelper* aiHelper;
	typedef int (AIHelper::*fn_ptr)(WorldObj*);
	typedef std::map<std::string, fn_ptr> functionMapper;
	functionMapper task_map;


public:
	AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer, WorldObj* obj);
	~AIManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




