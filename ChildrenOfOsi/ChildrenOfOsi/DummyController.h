#pragma once

#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"


class DummyController: public Manager
{
public:
	DummyController();
	~DummyController();

	virtual void execute_task(Task* current_task, MessageLog* mLog,
						TaskBuffer* tBuffer) final;

	int move_up();
	int move_down();
};



