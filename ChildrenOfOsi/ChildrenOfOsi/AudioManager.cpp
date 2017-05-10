#include "stdafx.h"
#include "AudioManager.h"
#include "fmod.hpp"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AudioManager Object Constructed");
	soundHelper = new SoundSystem();
	map1["Pause"] = &SoundSystem::pauseSound;
	map1["Unpause"] = &SoundSystem::unpauseSound;
	map2["PlaySound"] = &SoundSystem::playSound;
	map3["Change"] = &SoundSystem::changeSoundSource;
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
	auto it3 = map3.find(current_task->name);
	if (it0 == map0.end()&& it1 == map1.end() && it2 == map2.end() && it3 == map3.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	//execute 1 parameter functions
	else if(it0 == map0.end() && it2 == map2.end()&& it3 == map3.end()) {result = (soundHelper->*(it1->second))(current_task->source);}
	//execute 2 parameter functions
	else if (it0 == map0.end() && it1 == map1.end() && it3 == map3.end()) {result = (soundHelper->*(it2->second))(current_task->source, current_task->soundType);}
	//execute 3 prarameter functions
	else if (it0 ==map0.end() &&it1 == map1.end() && it2 == map2.end()) { result = (soundHelper->*(it3->second))(current_task->source, current_task->target,current_task->soundType); }
	//execute 0 prarameter functions
	else {result = (soundHelper->*(it0->second))();}

	if (result == 0) {current_task->updateStatus("COMPLETED");}
	else {current_task->updateStatus("FAILED");}
	this->send_result(current_task);


}
