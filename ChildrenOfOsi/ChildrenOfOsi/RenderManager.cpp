#include "stdafx.h"
#include "RenderManager.h"


RenderManager::RenderManager(MessageLog * _mLog, TaskBuffer * _tBuffer) : Manager(_mLog, _tBuffer)
{
	//renderHelper = new RenderHelper();
	LOG("RenderManager W/QT Object Constructed");
}

RenderManager::RenderManager(MessageLog * _mLog, TaskBuffer * _tBuffer, QuadTree * _renderQuadTree, ChildrenOfOsi* game_f, RiverObj* _rivObj) : Manager(_mLog, _tBuffer)
{
	LOG("RenderingManager W/QT Object Constructed");
	

	renderHelper = new RenderHelper(_renderQuadTree, _rivObj);
	renderHelper->manager = this;
	task_map["Init_Map"] = &RenderHelper::init_map;
	task_map["Draw_Frame"] = &RenderHelper::draw_frame;
	task_map["Move_Up"] = &RenderHelper::sprite_up;
	task_map["Move_Up_Right"] = &RenderHelper::sprite_right;
	task_map["Move_Up_Left"] = &RenderHelper::sprite_left;
	task_map["Move_Down"] = &RenderHelper::sprite_down;
	task_map["Move_Down_Right"] = &RenderHelper::sprite_right;
	task_map["Move_Down_Left"] = &RenderHelper::sprite_left;
	task_map["Move_Left"] = &RenderHelper::sprite_left;
	task_map["Move_Right"] = &RenderHelper::sprite_right;
	task_map["Stop"] = &RenderHelper::sprite_idle;
	task_map["Sprite_Update"] = &RenderHelper::sprite_update;
	task_map["Dialogue"] = &RenderHelper::drawDiaGui;
	task_map["HUD"] = &RenderHelper::drawHUD;
	task_map["Melee"] = &RenderHelper::sprite_atk;
	task_map["Spin"] = &RenderHelper::sprite_spin_atk;
	task_map["Fire"] = &RenderHelper::sprite_fire_atk;
	task_map["Hurt"] = &RenderHelper::sprite_hurt;
	task_map["GSword"] = &RenderHelper::setSwordGlow;
	task_map["GHeart"] = &RenderHelper::setHeartGlow;
	task_map["GFace"] = &RenderHelper::setFaceGlow;
	task_map["GQuestion"] = &RenderHelper::setQuestionGlow;
	

	

}

RenderManager::~RenderManager()
{
}

void RenderManager::register_manager()
{
	tBuffer->add_to_table("DRAW", this);
	tBuffer->add_to_table("MOVE", this);
	//tBuffer->add_to_table("RENDER", this);
	tBuffer->add_to_table("INTERACT", this);
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
			//current_task->updateStatus("FAILED");
			//this->send_result(current_task);
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