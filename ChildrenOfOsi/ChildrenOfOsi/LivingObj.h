#pragma once
#include "stdafx.h"
#include "WorldObj.h"

class LivingObj :
	public WorldObj
{
public:
	LivingObj();
	LivingObj(float x, float y, bool col);
	~LivingObj();
	int getHealth();
	void setHealth(int h);
	bool getAlive();
	void setAlive(bool v);
	void addHealth(int h);
private:
	int health;
	bool alive;
};

