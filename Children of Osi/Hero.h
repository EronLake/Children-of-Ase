#pragma once
#include "SplSoldier.h"
class Hero :
	public SplSoldier
{
public:
	Hero();
	Hero(float x, float y, bool col);
	~Hero();
private:
	int affinity;
};

