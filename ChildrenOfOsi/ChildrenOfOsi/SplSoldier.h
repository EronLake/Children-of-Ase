#pragma once
#include "stdafx.h"
#include "Soldier.h"
class SplSoldier :
	public Soldier
{
public:
	SplSoldier();
	SplSoldier(float x, float y, bool col);
	SplSoldier(Vector2f p_topLeft, float p_width, float p_height);
	~SplSoldier();
private:
};

