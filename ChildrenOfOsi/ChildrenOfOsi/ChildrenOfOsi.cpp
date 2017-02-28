#include "stdafx.h"
#include "ChildrenOfOsi.h"
#include "MemoryPool.h"
#include "memManager.h"

ChildrenOfOsi::ChildrenOfOsi(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	LOG("ChildrenOfOsi Object Constructed");
}


ChildrenOfOsi::~ChildrenOfOsi()
{
	LOG("ChildrenOfOsi Object Destroyed");
}
//////////////////////////////////////////////////////
//----------------------------------------------------


void ChildrenOfOsi::move_up(WorldObj * player)
{
	if (player == nullptr) {
		LOG("children of osi move up func, player obj is nullptr");
	}
	createTask("Move_Up", "MOVE", player);
}

void ChildrenOfOsi::move_left(WorldObj * player)
{
	createTask("Move_Left", "MOVE", player);
}

void ChildrenOfOsi::move_down(WorldObj * player)
{
	createTask("Move_Down", "MOVE", player);
}

void ChildrenOfOsi::move_right(WorldObj * player)
{
	createTask("Move_Right", "MOVE", player);
}

void ChildrenOfOsi::move_out(WorldObj * player)
{
	createTask("Move_Out", "MOVE", player);
}

void ChildrenOfOsi::move_up_left(WorldObj* player)
{
	createTask("Move_Up_Left", "MOVE", player);
}
void ChildrenOfOsi::move_up_right(WorldObj* player)
{
	createTask("Move_Up_Right", "MOVE", player);
}
void ChildrenOfOsi::move_down_left(WorldObj* player)
{
	createTask("Move_Down_Left", "MOVE", player);
}
void ChildrenOfOsi::move_down_right(WorldObj* player)
{
	createTask("Move_Down_Right", "MOVE", player);
}

void ChildrenOfOsi::stop(WorldObj* player) {
	createTask("Stop", "MOVE", player);
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

void ChildrenOfOsi::move_toward(WorldObj* obj) {
	createTask("Move", "AI", obj);
}
void ChildrenOfOsi::get_path(WorldObj* obj) {
	createTask("Path", "AI", obj);
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

void ChildrenOfOsi::talk(WorldObj * player)
{
	createTask("Talk", "INTERACT", player);
}

void ChildrenOfOsi::melee(WorldObj * player)
{
	createTask("Melee", "INTERACT", player);
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////

void ChildrenOfOsi::setSwordGlow(WorldObj* player)
{
	createTask("GSword", "DRAW", player);
}

void ChildrenOfOsi::setHeartGlow(WorldObj * player)
{
	createTask("GHeart", "DRAW", player);

}

void ChildrenOfOsi::setFaceGlow(WorldObj * player)
{
	createTask("GFace", "DRAW", player);

}

void ChildrenOfOsi::setQuestionGlow(WorldObj * player)
{
	createTask("GQuestion", "DRAW", player);

}

void ChildrenOfOsi::draw_frame(WorldObj * player)
{
	createTask("Draw_Frame", "DRAW", player);
}

void ChildrenOfOsi::drawDiaGui(WorldObj* player)
{
	createTask("Talk", "DRAW", player);
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////

void ChildrenOfOsi::add_hero(std::string key, float x, float y, bool col) {
	createTaskWithParams("Add_Hero", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_soldier(std::string key, float x, float y, bool col) {
	createTaskWithParams("Add_Soldier", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_spl_soldier(std::string key, float x, float y, bool col) {
	createTaskWithParams("Add_Spl_Soldier", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_livingObj(std::string key, float x, float y, bool col) {
	createTaskWithParams("Add_LivingObj", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_worldObj(std::string key, float x, float y, bool col) {
	createTaskWithParams("Add_WorldObj", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_Attack(std::string key, float x, float y, bool col, int d) {
	createTaskWithParams("Add_Attack", "MODIFY_POOL", key, x, y, col); //, d); Dmg might have to be defined separately
}

void ChildrenOfOsi::add_npc(std::string key, float x,float y, bool col) {
	createTaskWithParams("Add_NPC", "MODIFY_POOL", key, x, y, col);
}

void ChildrenOfOsi::add_texture(std::string key, float x=0, float y=0, bool col=0) {
	createTaskWithParams("Add_Texture", "MODIFY_POOL", key, x, y, col);
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void ChildrenOfOsi::play_sound(string name) {
	createTask(name, "SOUND");
}

//----------------------------------------------------
//----------------------------------------------------


void ChildrenOfOsi::createTask(std::string task_name, std::string type, WorldObj * objToUpdate)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	if (objToUpdate == nullptr) {
		LOG("childrenofosi createtask func, obj to update is a nullptr");
	}
	Task* new_task = new Task(task_name, task_status, type, objToUpdate);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void ChildrenOfOsi::createTaskWithParams(std::string task_name, std::string type, std::string key, float x, float y, bool col)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, key, x, y, col);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

/*void ChildrenOfOsi::createTaskForAttack(std::string task_name, std::string type, float x, float y, bool col, int d) {
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, x, y, col, d);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);

}/**/