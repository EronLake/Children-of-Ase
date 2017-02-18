#include "stdafx.h"
#include "Hero.h"
using namespace std;


Hero::Hero()
{
}

Hero::Hero(float x, float y, bool col) :SplSoldier(x, y, col)
{
	affinity = 0;
	cout << "Affinity: " << affinity << endl;
}

Hero::Hero(Vector2f p_topLeft, float p_width, float p_height):SplSoldier(p_topLeft,p_width,p_height)
{
}

Hero::~Hero()
{
}
