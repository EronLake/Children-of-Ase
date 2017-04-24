#include "stdafx.h"
#include "LivingObj.h"
using namespace std;

LivingObj::LivingObj()
{
	health = 1;
	max_health = 1;
	alive = true;
	setType(1);
}

LivingObj::LivingObj(float x, float y, bool col) : WorldObj(x, y, col)
{
	health = 1;
	max_health = 1;
	alive = true;
	setType(1);
}

LivingObj::LivingObj(Vector2f p_topLeft, float p_width, float p_height):WorldObj(p_topLeft,p_width,p_height)
{
	health = 1;
	max_health = 1;
	alive = true;
	setType(1);
}

LivingObj::~LivingObj()
{
}

int LivingObj::getHealth()
{
	return health;
}

void LivingObj::setHealth(int h)
{
	health = h;
	if (h > max_health)max_health = h;
}

bool LivingObj::getAlive()
{
	return alive;
}

void LivingObj::setAlive(bool v)
{
	alive = v;
}

void LivingObj::addHealth(int h)
{
	health += h;
	if (health > max_health)health = max_health;
}