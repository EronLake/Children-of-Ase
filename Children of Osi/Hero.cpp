#include "Hero.h"
#include <iostream>
#include <string>
using namespace std;


Hero::Hero()
{
}

Hero::Hero(float x, float y, bool col) :SplSoldier(x, y, col)
{
	affinity = 0;
	cout << "Affinity: " << affinity << endl;
}

Hero::~Hero()
{
}
