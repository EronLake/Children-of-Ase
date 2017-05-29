#include "stdafx.h"
#include "Attack.h"
#include "Soldier.h"
#include "Party.h"
#include "CheckClass.h"


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

	 Soldier* attacker = dynamic_cast<Soldier*>(this->get_creator());
	 if (CheckClass::isPlayer(attacker->getParty()->getLeader())) 
	 {
		 Player* player = dynamic_cast<Player*>(attacker->getParty()->getLeader());
		 (*target).addHealth(-dmg + (player->ori/10));
	 } else {
		 (*target).addHealth(-dmg);
	 }

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
	 switch (getDirection()) {
	 case WorldObj::DIRECTION_UP:
			 shiftY(-speed);
			 break;
	 case WorldObj::DIRECTION_DOWN:
			 shiftY(speed);
			 break;
	 case WorldObj::DIRECTION_LEFT:
			 shiftX(-speed);
			 break;
	 case WorldObj::DIRECTION_RIGHT:
			 shiftX(speed);
			 break;
	 }
 }

 bool Attack::beenHit(WorldObj* o) {
	 for (auto i = hitObjs.begin(); i != hitObjs.end(); ++i) {
		 if (*i == o) return true;
	 }
	 return false;
 }

 