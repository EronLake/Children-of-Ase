#include "stdafx.h"
#include "Attack.h"


Attack::Attack()
{
}

Attack::Attack(float x, float y, bool col) : WorldObj(x, y, col)
{
}

Attack::~Attack()
{
}

 void Attack::Hit(LivingObj *target)
{
	 (*target).addHealth(-dmg);
	 if (destroyOnCollision) {
		 Attack::~Attack();
	 }
}