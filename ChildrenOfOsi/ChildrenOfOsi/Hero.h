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
	Hero(int name, Vector2f p_topLeft, float p_width, float p_height);

	~Hero();
private:
	int affinity;
};

