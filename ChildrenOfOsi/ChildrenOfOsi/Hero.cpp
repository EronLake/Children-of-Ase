#include "stdafx.h"
#include "Hero.h"
using namespace std;


Hero::Hero()
{
}

Hero::Hero(int _name, float x, float y, bool col) :SplSoldier(x, y, col)
{
	affinity = 0;
	name = _name;
	cout << "Affinity: " << affinity << endl;
}

Hero::Hero(int name, Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
}

Hero::~Hero()
{
}
