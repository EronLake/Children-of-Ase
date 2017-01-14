#pragma once
#include "WorldObj.h"
#include <iostream>
#include <string>

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
private:
	int health;
	bool alive;
};

