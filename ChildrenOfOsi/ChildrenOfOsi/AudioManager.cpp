#include "stdafx.h"
#include "AudioManager.h"
#include "fmod.hpp"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AudioManager Object Constructed");
	soundHelper = new SoundSystem();
	task_map["Play"] = &SoundSystem::playSong1;
	task_map["Bump"] = &SoundSystem::playBump;
	task_map["Walk"] = &SoundSystem::playWalk;
}


AudioManager::~AudioManager()
{
	LOG("AudioManager Object Destroyed");
}

void AudioManager::register_manager()
{
	tBuffer->add_to_table("SOUND", this);
}

void AudioManager::execute_task(Task* current_task)
{
	int result;
	auto it = task_map.find(current_task->name);
	if (it == task_map.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else {
		result = (soundHelper->*(it->second))();
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);


}
