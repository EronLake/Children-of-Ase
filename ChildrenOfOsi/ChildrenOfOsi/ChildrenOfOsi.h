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
	void special(WorldObj * player, int num);
	void combat(WorldObj * player);
	void setSwordGlow(WorldObj* player);
	void setHeartGlow(WorldObj* player);
	void setFaceGlow(WorldObj* player);
	void setQuestionGlow(WorldObj* player);

	//functions for rendering
	void draw_frame(WorldObj* player);
	void drawDiaGui(WorldObj* player);
	void init_map(WorldObj* obj);

	//functions for creating objects in memory
	void add_hero(std::string key, float x, float y, bool col);
    void add_soldier(std::string key, float x, float y, bool col);
	void add_Attack(std::string key, float x, float y, bool col, int d);
	void add_spl_soldier(std::string key, float x, float y, bool col);
	void add_livingObj(std::string key, float x, float y, bool col);
	void add_worldObj(std::string key, float x, float y, bool col);
	void add_npc(std::string key, float x, float y, bool col);
	void add_texture(std::string key, float x, float y, bool col);
	void add_memory(std::string key, int hero_name, int t, int frames, vector<NPC*> p, string cat, string cont, string where,
					int why, int when);
	void add_action(std::string key, int utility, int why, Hero* owner, Hero* receiver, Hero* doer, std::string exe_name);
	void add_tag(std::vector<std::string> topicVec,std::string key);
	void add_conv_point(std::string topic,std::string temp,std::string name);

	//functions for audio
	void play_sound(string name);
	void change_song(string name,char* from, char* to);
	void creatTaskForAudio(std::string _name,  std::string _type, char* _source = nullptr, char* _target = nullptr);
	void createTask(std::string task_name, std::string type, WorldObj * objToUpdate = NULL);
	void createTaskWithNum(std::string task_name, std::string type, WorldObj * objToUpdate,int num);
	void ChildrenOfOsi::createTaskWithParams(std::string task_name, std::string type, std::string key, float x, float y, bool col);
	void ChildrenOfOsi::createTaskAddMem(std::string task_name, std::string type, std::string key, int hero_name, int t, int frames, 
											vector<NPC*> p, string cat, string cont, string where, int why, int when);
	void ChildrenOfOsi::createTaskAddAct(std::string task_name, std::string type, std::string key, int utility, int why, 
											Hero* owner, Hero* receiver, Hero* doer, std::string exe_name);
	void ChildrenOfOsi::createTaskNoObj(std::string task_name, std::string type, std::string topic, std::string temp, std::string key);
	void ChildrenOfOsi::createTaskTag(std::string task_name, std::string type, std::vector<std::string> topicVec, std::string key);

	//void ChildrenOfOsi::createTaskForAttack(std::string task_name, std::string type, float x, float y, bool col, int d);

};

