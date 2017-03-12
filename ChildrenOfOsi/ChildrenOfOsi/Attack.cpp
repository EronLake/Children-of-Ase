#include "stdafx.h"
#include "Attack.h"


Attack::Attack()
{
	setType(-1);
	dmg = 0;
	duration = 62; //-1 will mean infinity
	destroyOnCollision = true;
	speed = 0;
	cooldown = 62;
	pause = 62;
}

Attack::Attack(float x, float y, bool col) : WorldObj(x, y, col)
{
	setType(-1);
	dmg=0;
	duration=62; //-1 will mean infinity
	destroyOnCollision=true;
	speed=0;
	cooldown=62;
	pause=62;
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
	 hitObjs.push_back(target);
}

 bool Attack::updateDuration() {
	 if (duration>0)duration--;
	 if (duration == 0) {
		 hitObjs.clear();
		 return false;
	 }
	 return true;
 }
 void Attack::move() {
	 std::string d = getDirection();
	 if (d.compare("UP")==0) {
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