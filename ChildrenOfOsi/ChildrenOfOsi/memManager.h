
#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"


class memManager : public Manager
{
public:
	memManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~memManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

};