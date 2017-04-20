#include "stdafx.h"
#include "Hero.h"
#include "NPC.h"
#include "Party.h"
#include "ActionPool.h"

using namespace std;


Hero::Hero()
{
	//initializes all 4 action pools for each hero
	for (int i = 1; i <= 5; i++)
	{
		if (i != this->name)
		{
			this->actionPool_map[i] = new ActionPool(this);
		}
	}
	action_timer = 0; //initialized to one so the check doesn't go below 0
	set_killable(false);
}

Hero::Hero(int _name, float x, float y, bool col) :SplSoldier(x, y, col)
{
	name = _name;
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	for (int i = 1; i < 6; i++) {
		if(i!=name)rel[i] = new Relationship();
	}
	setType(5);
	traits = new Personality();
	//planner = new Planner(this);

	//initializes all 4 action pools for each hero
	for (int i = 1; i <= 5; i++)
	{
		if (i!= this->name)
		{
			this->actionPool_map[i] = new ActionPool(this);
		}
	}
	action_timer = 0; //initialized to one so the check doesn't go below 0
	set_killable(false);
}



Hero::Hero(int _name, Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
	name = _name;
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	for (int i = 1; i < 6; i++) {
		if (i != name)rel[i] = new Relationship();
	}
	setType(5);

	//initializes all 4 action pools for each hero
	for (int i = 1; i <= 5; i++)
	{
		if (i != this->name)
		{
			this->actionPool_map[i] = new ActionPool(this);
		}
	}
	traits = new Personality();
	action_timer = 0; //initialized to one so the check doesn't go below 0
	set_killable(false);
}

Hero::~Hero()
{
	//initializes all 4 action pools for each hero
	for (auto itr = this->actionPool_map.begin(); itr != this->actionPool_map.end(); itr++)
	{
		delete itr->second;
	}

	delete(traits);
	for (int i = 1; i < 6; i++) {
		if (i != name)
			delete(rel[i]);
	}
	action_timer = 0; //initialized to one so the check doesn't go below 0
}

/*void Hero::addRelationship(int hero) {
	rel[hero] =new Relationship();
};*/

void Hero::setPersonality(int a, int k, int h, int p, int r, int e, int g){
	traits->setAggression(a);
	traits->setKindness(k);
	traits->setHonor(h);
	traits->setPride(p);
	traits->setRecklessness(r);
	traits->setExtroversion(e);
	traits->setGreed(g);
};

Memory* Hero::find_mem(std::string mem_name)
{
	for (int i = 0; i < memories.size(); i++) 
	{
		if (memories[i]->getContent() == mem_name)
		{
			return memories[i];
		}
	}
	return nullptr;
}

//overloads a soldier function
/*void Hero::defeat()
{
	//this->getParty()->removeSoldier(this,true);
	incapacitated = true;
}*/

//overloads a soldier function
/*void Hero::kill()
{
	this->getParty()->removeSoldier(this,false);
	this->setParty(NULL);
}*/

vector<pair<Action*, int>> Hero::get_quests() {
	vector<pair<Action*, int>> tmp;
	for (auto it = quests.begin(); it != quests.end(); ++it) {
		tmp.push_back({ it->first, it->second });
	}
	return tmp;
}
/*
void Hero::init_act_pools(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	//iterates through every player
	for (auto itr = Containers::hero_table.begin(); itr != Containers::hero_table.end(); itr++)
	{
		if (itr->second->name != name)
		{
			ActionConfig::import_config(gameplay_func, tBuffer, this, itr->second);
		}
	}
	return;
}
*/

int Hero::update_action_timer() {
	if (action_timer > 0) {
		action_timer--;
	}
	return action_timer;
}

void Hero::decrement_quest_time() {
	for (auto it = quests.begin(); it != quests.end();) {
		int s=it->second;
		if (s > 0)it->second = --s;
		if (s == 0) {
			//it->first->apply_postconditions(false);
			it=quests.erase(it);
		}
		else {
			++it;
		}
	}
}