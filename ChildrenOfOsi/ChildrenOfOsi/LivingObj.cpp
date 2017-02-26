#include "stdafx.h"
#include "LivingObj.h"
using namespace std;

LivingObj::LivingObj()
{
}

LivingObj::LivingObj(float x, float y, bool col) : WorldObj(x, y, col)
{
	health = 1;
	alive = true;
	cout << "Health: " << health << endl;
	cout << "Alive: " << alive << endl;
}

LivingObj::LivingObj(Vector2f p_topLeft, float p_width, float p_height):WorldObj(p_topLeft,p_width,p_height)
{
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
}