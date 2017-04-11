#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
#include "Relationship.h"
#include "Personality.h"
#include "Memory.h"


class ActionPool;
class Party;

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
	//Planner* planner;

	//used to hold the 4 planners for each of the other heroes
	std::unordered_map<int,ActionPool*> actionPool_map; //int is the receiver name

    int name;

	int mem_counter = 0;
	vector<Memory*> memories;
	Memory* find_mem(std::string mem_name);

	Party* cur_party;
	virtual void defeat();
	void kill();

	bool incapacitated;

	//void addRelationship(int hero);
	void setPersonality(int a, int k, int h, int p, int r, int e, int g);

	void add_quest(Action* a, int time) { quests[a]=time; };
	void remove_quest(Action* a) { quests.erase(quests.find(a)); };

    vector<pair<Action*,int>> get_quests();

	void decrement_quest_time();

private:

	std::unordered_map<Action*,int> quests;
	//now in the action config
	//void init_act_pools(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer);
};

