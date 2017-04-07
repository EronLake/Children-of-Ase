#include "stdafx.h"
#include "Hero.h"
#include "NPC.h"
#include "Party.h"

using namespace std;


Hero::Hero()
{
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
	//planner = new Planner(this);
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
}

Hero::~Hero()
{
}

void Hero::addRelationship(int hero) {
	rel[hero] =new Relationship();
};

void Hero::setPersonality(int a, int k, int h, int p, int r, int e, int g){
	traits = new Personality();
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
void Hero::defeat()
{
	this->getParty()->removeSoldier(this,true);
	incapacitated = true;
}

//overloads a soldier function
void Hero::kill()
{
	this->getParty()->removeSoldier(this,false);
	this->setParty(NULL);
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