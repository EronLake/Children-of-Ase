#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
}

Projectile::Projectile(float x, float y, bool col) : WorldObj(x, y, col)
{
}

Projectile::~Projectile()
{
}

 void Projectile::Hit(LivingObj *target)
{
	 (*target).addHealth(-dmg);
	 if (destroyOnCollision) {
		 Projectile::~Projectile();
	 }
}