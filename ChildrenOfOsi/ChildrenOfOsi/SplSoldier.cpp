#include "stdafx.h"
#include "SplSoldier.h"
using namespace std;


SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(float x, float y, bool col) :Soldier(x, y, col)
{
	ase = 10;
	setType(4);
}

SplSoldier::SplSoldier(Vector2f p_topLeft, float p_width, float p_height):Soldier(p_topLeft,p_width,p_height)
{
	ase = 10;
	setType(4);
}

SplSoldier::~SplSoldier()
{
}

void SplSoldier::setAse(int a)
{
	ase = a;
}

int SplSoldier::getAse()
{
	return ase;
}
