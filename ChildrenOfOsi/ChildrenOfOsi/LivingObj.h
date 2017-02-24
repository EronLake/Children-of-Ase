#pragma once
#include "stdafx.h"
#include "WorldObj.h"

class LivingObj :
	public WorldObj
{
public:
	LivingObj();
	LivingObj(float x, float y, bool col);
	LivingObj(Vector2f p_topLeft, float p_width, float p_height);
	~LivingObj();
	int getHealth();
	void setHealth(int h);
	bool getAlive();
	void setAlive(bool v);
	void addHealth(int h);
	Vector2f goal;
private:
	int health;
	bool alive;
};

