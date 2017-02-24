#include "stdafx.h"
#include "AIManager.h"



AIManager::AIManager(MessageLog* _mLog, TaskBuffer* _tBuffer, AIHelper* ai)
	: Manager(_mLog, _tBuffer)
{
	LOG("AIManager Object Constructed");
	aiHelper = ai;
	aiHelper->manager = this;
	task_map["Path"] = &AIHelper::astar_search;
	task_map["Move"] = &AIHelper::plan_step;

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
	NPC* obj;
	if (!(obj = CheckClass::isNPC(current_task->objToUpdate))) {
		result = 1;
		LOG("Error: No movable object");
	}
	else
	{
		auto it = task_map.find(current_task->name);
		if (it == task_map.end()) {
			result = 1;
			LOG("Error: Task '" << current_task->name << "' does not exist.");
		}
		else {
			result = (aiHelper->*(it->second))(obj);
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
