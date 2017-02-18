#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
class Hero :
	public SplSoldier
{
public:
	int name;

	Hero();
	Hero(int name, float x, float y, bool col);
	~Hero();
private:
	int affinity;
};

