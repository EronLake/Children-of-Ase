#include "stdafx.h"
#include "AudioManager.h"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("AudioManager Object Constructed");
	soundsystem = new SoundSystemClass();
	FnMap["playSong1"] = &SoundSystemClass::playSong1;
	//////////////////////////////////////
}


AudioManager::~AudioManager()
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("AudioManager Object Destroyed");
	//////////////////////////////////////
}

void AudioManager::register_manager()
{
	//THIS IS WHAT YOU EDIT
	//////////////////////////////////////
	tBuffer->add_to_table("AUD", this);
	//////////////////////////////////////
}

void AudioManager::execute_task(Task* current_task)
{
	if (current_task->name == "playSong1") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = (soundsystem->*(FnMap[current_task->name]))();
		//(moveHelper->*(it->second))(current_task->objToUpdate)
		//////////////////////////////////////
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	
	else
	{
		LOG("Error: Task name does not exist"); //perror?
	}
}

//WRITE EQUIVLENT FUNCTIONS IN A SEPARATE CLASS FILE 
//////////////////////////////////////


//////////////////////////////////////