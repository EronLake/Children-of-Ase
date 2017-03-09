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
	 for (int i = 0; i < hitObjs.size(); i++) {
		 if (target == hitObjs[i])return;
	 }
	 (*target).addHealth(-dmg);
	 if (destroyOnCollision) {
		 Attack::~Attack();
	 } else {
		 hitObjs.push_back(target);
	 }
}

 bool Attack::updateDuration() {
	 duration--;
	 if (duration == 0) {
		 hitObjs.clear();
		 return false;
	 }
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