#include "stdafx.h"
#include "Hero.h"
#include "NPC.h"
using namespace std;


Hero::Hero()
{
}

Hero::Hero(int _name, float x, float y, bool col) :SplSoldier(x, y, col)
{
	name = _name;
	float speed = 2.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	
	//init relationship for all heroes and shango. remove the one that is the hero's own
	for (int i = 1; i < 6; i++) {
		relationMap[i] = new Relationship();
	}
}

Hero::Hero(int _name, Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
	name = _name;
	float speed = 2.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	
	//init relationship for all heroes and shango. remove the one that is the hero's own
	for (int i = 1; i < 6; i++) {
		relationMap[i] = new Relationship();
	}
}

Hero::~Hero()
{
}

void Hero::addRelation(int p_heroNum, Relationship * p_relations)
{
	relationMap[p_heroNum] = p_relations;
}

void Hero::removeRelation(int p_heroNum)
{
}

Relationship * Hero::getRelation(int p_heroNum)
{
	return nullptr;
}
