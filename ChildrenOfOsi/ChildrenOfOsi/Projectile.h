#pragma once
#include "stdafx.h"
#include "LivingObj.h"

class Projectile :
	public WorldObj
{
public:
	Projectile();
	Projectile(float x, float y, bool col);// , int d);
	~Projectile();
	void Hit(LivingObj *target);
	void setDmg(int d) { dmg = d; };
	int getDmg() { return dmg; };
	void setDuration(int d) { duration = d; };
	int getDuration() { return duration; };
	void setDestroy(bool d) { destroyOnCollision = d; };
	bool getDestroy() {return destroyOnCollision;};
	void setSpeed(float s) { speed=s; };
	float getSpeed() { return speed; };
private:
	int dmg;
	int duration; //-1 will mean infinity
	bool destroyOnCollision;
	float speed;
};
