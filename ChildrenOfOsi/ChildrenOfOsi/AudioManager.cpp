#include "stdafx.h"
#include "AudioManager.h"
#include "fmod.hpp"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AudioManager Object Constructed");
	soundHelper = new SoundSystem();
	sound_map["Play"] = &SoundSystem::playSong1;
	sound_map["Bump"] = &SoundSystem::playBump;
	sound_map["Walk"] = &SoundSystem::playWalk;
	sound_map["Sixers"] = &SoundSystem::playSixers;
	function_map["Pause"] = &SoundSystem::pauseSound;
	function_map["Unpause"] = &SoundSystem::unpauseSound;
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
	auto it = sound_map.find(current_task->name);
	auto it2 = function_map.find(current_task->name);
	if (it == sound_map.end()&& it2 == function_map.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else {
		if (current_task->name == "Pause" || current_task->name == "Unpause") {
			result = (soundHelper->*(it2->second))("walk_loop.wav");
			
		}
		else {
			result = (soundHelper->*(it->second))();
		}
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);


}
