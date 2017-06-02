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
	static const int health_multiplier = 60;
	int getHealth();
	void setHealth(int h);
	bool getAlive();
	void setAlive(bool v);
	void addHealth(int h);
	void add_to_max_health(int h) { max_health += (h*health_multiplier); };
	void set_max_health(int h) { max_health = (h*health_multiplier); };
	int get_max_health() { return (max_health/health_multiplier); };
	Vector2f goal;
	void regenHealth();
private:
	int health;
	int max_health;
	bool alive;
};

