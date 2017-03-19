#include "stdafx.h"
#include "AudioManager.h"
#include "fmod.hpp"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AudioManager Object Constructed");
	soundHelper = new SoundSystem();
	map0["Play"] = &SoundSystem::playSong1;
	map0["Bump"] = &SoundSystem::playBump;
	map0["Walk"] = &SoundSystem::playWalk;
	map0["Sixers"] = &SoundSystem::playSixers;
	map1["Pause"] = &SoundSystem::pauseSound;
	map1["Unpause"] = &SoundSystem::unpauseSound;
	map2["Change"] = &SoundSystem::changeSoundSource;
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
	auto it0 = map0.find(current_task->name);
	auto it1 = map1.find(current_task->name);
	auto it2 = map2.find(current_task->name);
	if (it0 == map0.end()&& it1 == map1.end() && it2 == map2.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else if(it0 == map0.end() && it2 == map2.end()) {

			result = (soundHelper->*(it1->second))(current_task->source);
			
		
		
	}
	else if (it0 == map0.end() && it1 == map1.end()) {

		result = (soundHelper->*(it2->second))(current_task->source, current_task->target);

	}
	else {
		result = (soundHelper->*(it0->second))();
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);


}
