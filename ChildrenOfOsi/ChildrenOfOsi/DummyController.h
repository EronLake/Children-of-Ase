#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"


class DummyController: public Manager
{
public:
	DummyController(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~DummyController();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

	int move_up();
	int move_down();
};



