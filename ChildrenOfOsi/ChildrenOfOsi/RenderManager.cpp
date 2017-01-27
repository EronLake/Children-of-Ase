#include "stdafx.h"
#include "RenderManager.h"


RenderManager::RenderManager(MessageLog* _mLog, TaskBuffer* _tBuffer) : Manager(_mLog, _tBuffer)
{
	LOG("RenderManager Object Constructed");
}

RenderManager::RenderManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _physicsQuadTree) : Manager(_mLog, _tBuffer)
{
	renderHelper = new RenderHelper(_physicsQuadTree);
	LOG("RenderManager W/QT Object Constructed");
}

RenderManager::~RenderManager()
{
}

void RenderManager::register_manager()
{
	tBuffer->add_to_table("DRAW", this);
	tBuffer->add_to_table("SPRITE", this);
	tBuffer->add_to_table("RENDER", this);
}

void RenderManager::execute_task(Task* current_task)
{
	int result;
	if (current_task->objToUpdate == NULL) {
		result = 1;
		LOG("Error: No player object");
		current_task->updateStatus("FAILED");
	}
	else {
		if (current_task->name == "Draw_Frame") {
		}
		else if (current_task->name == "Sprite_Change") {
		}
		else if (current_task->name == "Sprite_Update") {
		}
		else if (current_task->name == "Render_Objects") {
		}
		else {
			result = 1;
			LOG("Error: Task name does not exist"); //perror?
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