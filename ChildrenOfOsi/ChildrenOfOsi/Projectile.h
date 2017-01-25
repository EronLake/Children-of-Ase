#pragma once
#include "LivingObj.h"

class Projectile :
	public WorldObj
{
public:
	Projectile();
	Projectile(float x, float y, bool col, int d);
	~Projectile();
	void Hit(LivingObj *target);
protected:
	int dmg;
};

