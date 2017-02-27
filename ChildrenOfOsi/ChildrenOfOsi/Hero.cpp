#include "stdafx.h"
#include "Hero.h"
#include "NPC.h"
using namespace std;


Hero::Hero()
{
}

Hero::Hero(int _name, float x, float y, bool col) :SplSoldier(x, y, col)
{
	affinity = 0;
	name = _name;
	cout << "Affinity: " << affinity << endl;
	float speed = 2.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
}

Hero::Hero(int _name, Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
	affinity = 0;
	name = _name;
	float speed = 2.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
}

Hero::~Hero()
{
}
