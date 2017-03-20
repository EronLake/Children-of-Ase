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
	
	typedef int (SoundSystem::*fn_ptr_0)();
	typedef int (SoundSystem::*fn_ptr_1)(std::string name);
	typedef int (SoundSystem::*fn_ptr_2)(char* from, char* to);
	typedef std::map<std::string, fn_ptr_0> zeroparamMapper;
	typedef std::map<std::string, fn_ptr_1> oneparamMapper;
	typedef std::map<std::string, fn_ptr_2> twoparamMapper;
	zeroparamMapper map0;
	oneparamMapper map1;
	twoparamMapper map2;

public:
	AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~AudioManager();
	SoundSystem* soundHelper;

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
};
