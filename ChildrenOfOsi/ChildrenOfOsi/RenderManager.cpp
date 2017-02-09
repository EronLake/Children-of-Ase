#include "stdafx.h"
#include "RenderManager.h"


RenderManager::RenderManager(MessageLog * _mLog, TaskBuffer * _tBuffer) : Manager(_mLog, _tBuffer)
{
	//renderHelper = new RenderHelper();
	LOG("RenderManager W/QT Object Constructed");
}

RenderManager::RenderManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _renderQuadTree) : Manager(_mLog, _tBuffer)
{
	LOG("RenderingManager W/QT Object Constructed");
	renderHelper = new RenderHelper(_renderQuadTree);
	task_map["Draw_Frame"] = &RenderHelper::draw_frame;
	task_map["Sprite_Change"] = &RenderHelper::sprite_change;
	task_map["Sprite_Update"] = &RenderHelper::sprite_update;

}

RenderManager::~RenderManager()
{
}

void RenderManager::register_manager()
{
	tBuffer->add_to_table("DRAW", this);
	tBuffer->add_to_table("SPRITE", this);
	//tBuffer->add_to_table("RENDER", this);
}

void RenderManager::execute_task(Task* current_task)
{
	int result;
	if (current_task->objToUpdate == nullptr) {
		result = 1;
		LOG("Error: No obj to draw");
		current_task->updateStatus("FAILED");
	}
	else {
		auto it = task_map.find(current_task->name);
		if (it == task_map.end()) {
			result = 1;
			LOG("Error: Task '" << current_task->name << "' does not exist.");
			current_task->updateStatus("FAILED");
			this->send_result(current_task);
		}
		else {
			LOG("EXECUTION PRIOR TO RESULT");
			result = (renderHelper->*(it->second))(current_task->objToUpdate);

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