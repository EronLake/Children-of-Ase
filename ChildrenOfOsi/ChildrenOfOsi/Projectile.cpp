#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
}

Projectile::Projectile(float x, float y, bool col) : WorldObj(x, y, col)
{
	//dmg = d;
}

Projectile::~Projectile()
{
}

 void Projectile::Hit(LivingObj *target)
{
	 (*target).addHealth(-dmg);
}
 void Projectile::setDmg(int d) {
	 dmg = d;
 }