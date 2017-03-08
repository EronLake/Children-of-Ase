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

 bool Attack::updateDuration() {
	 duration--;
	 if (duration == 0)return false;
	 return true;
 }
 void Attack::move() {
	 std::string d = getDirection();
	 if (d.compare("UP")) {
		 shiftY(-speed);
	 }
	 else if (d.compare("DOWN") == 0) {
		 shiftY(speed);
	 }
	 else if (d.compare("LEFT") == 0) {
		 shiftX(-speed);
	 }
	 else if (d.compare("RIGHT") == 0) {
		 shiftX(speed);
	 }
 }