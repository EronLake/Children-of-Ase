#include "stdafx.h"
#include "SplSoldier.h"
using namespace std;


SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(float x, float y, bool col) :Soldier(x, y, col)
{
	setType(4);
	this->setMaxAse(100);
	this->setAse(100);
}

SplSoldier::SplSoldier(Vector2f p_topLeft, float p_width, float p_height):Soldier(p_topLeft,p_width,p_height)
{
	setType(4);
	this->setMaxAse(100);
	this->setAse(100);
}

SplSoldier::~SplSoldier()
{
}
