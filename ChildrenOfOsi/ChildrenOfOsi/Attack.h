#pragma once
#include "stdafx.h"
#include "LivingObj.h"

class Attack :
	public WorldObj
{
public:
	Attack();
	Attack(float x, float y, bool col);// , int d);
	~Attack();
	void Hit(LivingObj *target);
	void setDmg(int d) { dmg = d; };
	int getDmg() { return dmg; };
	void setDuration(int d) { duration = d; };
	bool updateDuration();
	int getDuration() { return duration; };
	void setDestroy(bool d) { destroyOnCollision = d; };
	bool getDestroy() {return destroyOnCollision;};
	void setSpeed(float s) { speed=s; };
	float getSpeed() { return speed; };
	void setCoolDown(int c) { cooldown = c; };
	int getCoolDown() { return cooldown; };
	void move();
	void setFrom(WorldObj* o) { fromObj = 0; };
	WorldObj* getFrom() { return fromObj; };
	void setPause(int p) { pause = p; };
	void updatePause() { pause--; };
	int getPause() { return pause; };
private:
	int dmg;
	int duration; //-1 will mean infinity
	bool destroyOnCollision;
	float speed;
	int cooldown;
	int pause;
	WorldObj* fromObj;
};
