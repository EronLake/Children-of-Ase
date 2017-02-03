#include "stdafx.h"
#include "AudioManager.h"


AudioManager::AudioManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	//THIS IS WHAT YOU EDIT (JUST THE NAME IN PRINT STATEMENT)
	//////////////////////////////////////
	LOG("AudioManager Object Constructed");
	soundsystem = new SoundSystemClass();
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
	//might need to take in move as well
	tBuffer->add_to_table("AUD", this);
	//////////////////////////////////////
}

void AudioManager::execute_task(Task* current_task)
{
	if (current_task->name == "Play_SFX") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = soundsystem->doNothing();
		//////////////////////////////////////
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "Play_Music") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = soundsystem->doNothing();
		//////////////////////////////////////
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "Toggle_SFX") {
		//THIS IS WHAT YOU EDIT
		//////////////////////////////////////
		int result = soundsystem->doNothing();
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