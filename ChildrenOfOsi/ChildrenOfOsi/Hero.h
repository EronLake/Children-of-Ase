#pragma once
#include "stdafx.h"
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

