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
	typedef int (SoundSystem::*fn_ptr_2)(std::string name, RegionState::soundType type);
	typedef int (SoundSystem::*fn_ptr_3)(char* from, char* to, RegionState::soundType type);
	typedef std::map<std::string, fn_ptr_0> zero_param_mapper;
	typedef std::map<std::string, fn_ptr_1> one_param_mapper;
	typedef std::map<std::string, fn_ptr_2> two_param_mapper;
	typedef std::map<std::string, fn_ptr_3> three_param_mapper;
	zero_param_mapper map0;
	one_param_mapper map1;
	two_param_mapper map2;
	three_param_mapper map3;

public:
	AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~AudioManager();
	SoundSystem* soundHelper;

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
};
