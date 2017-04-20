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
	void add_to_max_health(int h) { max_health += h; };
	void set_max_health(int h) { max_health = h; };
	int get_max_health() { return max_health; };
	Vector2f goal;
private:
	int health;
	int max_health;
	bool alive;
};

