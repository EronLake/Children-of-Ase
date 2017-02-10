#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "Manager.h"
#include "ChildrenOfOsi.h"
#include "MemoryPool.h"
#include "memManager.h"
#include "TaskBuffer.h"


class TaskBufferTestSuite
{
public:
	TaskBufferTestSuite();
	~TaskBufferTestSuite();

	bool execute_tests(); //Runs all other tests and checks them

	bool TaskBuffer_constructor_test();
	bool TaskBuffer_destructor_test();
	bool run_test();
	bool assignTask_test();
	bool isEmpty_test();
	bool empty_test();
	bool push_test();
	bool pop_test();
	
};

