#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "MemoryPool.h"
#include "MemNode.h"
#include "TaskBufferTestSuite.h"
#include "AudioTestSuite.h"
#include "PhysicsTestSuite.h"
#include "MemoryTestSuite.h"

class TestManager : public Manager
{
private:


public:
	bool run_unit_tests();
	TestManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~TestManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};




