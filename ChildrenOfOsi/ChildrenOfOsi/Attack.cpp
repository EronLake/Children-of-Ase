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
	canCancel = true;
	aseCost=0;
	staminaCost = 0;
	next = nullptr;
	turn = false;
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
	canCancel = true;
	aseCost = 0;
	staminaCost = 0;
	next = nullptr;
	turn = false;
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
	 int d = getDirection();
	 if (d == 8) {
		 shiftY(-speed);
	 }
	 else if (d == 2) {
		 shiftY(speed);
	 }
	 else if (d == 4) {
		 shiftX(-speed);
	 }
	 else if (d == 6) {
		 shiftX(speed);
	 }
 }

 bool Attack::beenHit(WorldObj* o) {
	 for (auto i = hitObjs.begin(); i != hitObjs.end(); ++i) {
		 if (*i == o) return true;
	 }
	 return false;
 }

 