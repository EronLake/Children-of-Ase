#include "stdafx.h"
#include "AIManager.h"



AIManager::AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
	LOG("AIManager Object Constructed");

}

AIManager::AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer, WorldObj* obj)
	: Manager(_mLog, _tBuffer)
{
	LOG("AIManager W/World Object Constructed");
	aiHelper = new AIHelper(obj);

	task_map["Shortest_Path"] = &AIHelper::Astar;
}

AIManager::~AIManager()
{
	LOG("AIManager Object Destroyed");
	delete(aiHelper);
}

void AIManager::register_manager()
{
	tBuffer->add_to_table("AI", this);
}

void AIManager::execute_task(Task* current_task)
{
	int result;
	
	auto it = task_map.find(current_task->name);
	if (it == task_map.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else {
		result = (aiHelper->*(it->second))(current_task->objToUpdate);
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);
}
