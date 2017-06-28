#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
#include "Relationship.h"
#include "Personality.h"
#include "Memory.h"
#include "ConversationLogObj.h"

class ActionPool;
//class Party;
class ConversationLogObj;

class Hero :
	public SplSoldier
{
public:
	
	Hero();
	Hero(int name, float x, float y, bool col);
	Hero(int name, Vector2f p_topLeft, float p_width, float p_height);
	~Hero();

	unordered_map<int, Relationship*> rel;
	Personality* traits;
	std::vector<ConversationLogObj*> conversation_log;
	//Planner* planner;

	//used to hold the 4 planners for each of the other heroes
	std::unordered_map<int,ActionPool*> actionPool_map; //int is the receiver name

    int name;
	char* song;

	int mem_counter = 0;
	vector<Memory*> memories;
	Memory* find_mem(std::string mem_name);

	//Party* cur_party;
	//void defeat();
	//void capacitate();
	//void kill();

	//void addRelationship(int hero);
	void setPersonality(int a, int k, int h, int p, int r, int e, int g);

	void add_quest(Action* a, int time) { quests[a]=time; };
	void remove_quest(Action* a) { quests.erase(a); };

    vector<pair<Action*,int>> get_quests();

	void decrement_quest_time();

	int get_action_timer() { return action_timer; }
	int update_action_timer();
	void init_action_timer(int wait_time) {action_timer = wait_time;}

	int get_busy() { return busy; }
	void set_busy(int b) { busy=b; }

	static constexpr int NOT_BUSY = 0;
	static constexpr int BUSY_TRAVEL = 1;
	static constexpr int BUSY_MARCH = 2;
	static constexpr int BUSY_REC_TALK = 3;
	static constexpr int BUSY_REC_FIGHT = 4;
	static constexpr int BUSY_TALK = 5;
	static constexpr int BUSY_FIGHT = 6;

	//for suggested actions(move tos)
	static constexpr int NOT_SUGG_ACT = 0;
	static constexpr int SUGG_ACT = 1;
	static constexpr int FAIL_SUGG_ACT = 2;
	static constexpr int SUCC_SUGG_ACT = 3;
	int SUGG_ACT_STATUS;

	static constexpr int NOT_QUEST = 0;
	static constexpr int IN_PROGRESS = 1;
	static constexpr int FAIL_QUEST = 2;
	static constexpr int SUCC_QUEST = 3;
	typedef std::unordered_map<int, int> status_map; // first part of pair is quest owner, second is quest status
	status_map quest_status;

	
	std::unordered_map<std::string, int> trait_vec;
	int get_range_cap(Action* a);

	int get_strength() { return strength; };
	void add_strength(int s) { strength += s; if (strength > 100)strength = 100; if (strength < 0)strength = 0; };
	void set_strength(int s) { strength = s; };

private:

	std::unordered_map<Action*,int> quests;
	
	int action_timer;

	int busy;
	int strength;
	//now in the action config
	//void init_act_pools(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
};

