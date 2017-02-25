#pragma once
#include "common.h"
#include "Task.h"
#include "TaskBuffer.h"
#include "MessageLog.h"
#include "Player.h"


class ChildrenOfOsi
{
private:
	MessageLog* mLog;
	TaskBuffer* tBuffer;
public:
	ChildrenOfOsi(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~ChildrenOfOsi();

	//functions for moving
	void move_up(WorldObj * player);
	void move_left(WorldObj * player);
	void move_down(WorldObj * player);
	void move_right(WorldObj * player);
	void move_up_left(WorldObj* player);
	void move_up_right(WorldObj* player);
	void move_down_left(WorldObj* player);
	void move_down_right(WorldObj* player);
	void move_out(WorldObj * player);
	void stop(WorldObj* player);
	void move_toward(WorldObj* player);
	void get_path(WorldObj* obj);
	void talk(WorldObj * player);
	void melee(WorldObj * player);
	void setSwordGlow(WorldObj* player);
	void setHeartGlow(WorldObj* player);
	void setFaceGlow(WorldObj* player);
	void setQuestionGlow(WorldObj* player);

	//functions for rendering
	void draw_frame(WorldObj* player);
	void drawDiaGui(WorldObj* player);

	//functions for creating objects in memory
	void add_hero(std::string key, float x, float y, bool col);
    void add_soldier(std::string key, float x, float y, bool col);
	void add_projectile(std::string key, float x, float y, bool col, int d);
	void add_spl_soldier(std::string key, float x, float y, bool col);
	void add_livingObj(std::string key, float x, float y, bool col);
	void add_worldObj(std::string key, float x, float y, bool col);
	void add_npc(std::string key, float x, float y, bool col);
	//void add_texture(std::string key, float x, float y, bool col);

	//functions for audio
	void play_sound(string name);

	void createTask(std::string task_name, std::string type, WorldObj * objToUpdate = NULL);
	void ChildrenOfOsi::createTaskWithParams(std::string task_name, std::string type, std::string key, float x, float y, bool col);
	//void ChildrenOfOsi::createTaskForProjectile(std::string task_name, std::string type, float x, float y, bool col, int d);

};

