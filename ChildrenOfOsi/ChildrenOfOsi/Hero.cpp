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
}

Hero::Hero(int _name, Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
	name = _name;
	float speed = 2.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
}

Hero::~Hero()
{
}

void Hero::addRelationship(Hero* hero) {
	rel.emplace(hero->getName(),Relationship());
}
