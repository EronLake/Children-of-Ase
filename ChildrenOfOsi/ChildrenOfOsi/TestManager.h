#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "MemoryPool.h"
#include "MemNode.h"

class TestManager : public Manager
{
private:


public:
	int run_unit_tests();
	TestManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~TestManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




