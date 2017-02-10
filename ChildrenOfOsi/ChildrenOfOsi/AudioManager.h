#pragma once
#include "stdafx.h"
#include "common.h"
#include "Task.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "SoundSystem.h"


class AudioManager : public Manager
{
private:
	SoundSystem* soundHelper;
	typedef int (SoundSystem::*fn_ptr)();
	typedef std::map<std::string, fn_ptr> functionMapper;
	functionMapper task_map;

public:
	AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~AudioManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
};
