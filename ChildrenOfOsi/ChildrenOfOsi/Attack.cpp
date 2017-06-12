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
	 //gives party an ori boost if the leader is the player
	 if (CheckClass::isPlayer(attacker->getParty()->getLeader())) 
	 {
		 Player* player = dynamic_cast<Player*>(attacker->getParty()->getLeader());
		 (*target).addHealth(-(dmg + ((player->get_strength() - 50)/10) + ((player->ori-50)/10)));
	 } else if (CheckClass::isHero(attacker->getParty()->getLeader()))
	 {
		Hero* hero = dynamic_cast<Hero*>(attacker->getParty()->getLeader());
		 (*target).addHealth(-(dmg + (hero->get_strength() - 50) / 10));
	 } else {
		 (*target).addHealth(-dmg);
	 }

	 //gives player a boost if in exhalted form
	 if (CheckClass::isPlayer(attacker)) {
		 Player* player = dynamic_cast<Player*>(attacker);
		 if (player->exalted_form == 1) {
			 (*target).addHealth(-dmg/3);
		 }
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
	 if (this->name==Attack::SHIELD) {
		 int x = this->getWidth()*(1 + (speed / 35)) - this->getWidth();
		 int y = this->getHeight()*(1 + (speed / 35)) - this->getHeight();
		 this->shiftX(-(x/2));
		 this->shiftY(-(y/2));
		 this->setWidth(this->getWidth()*(1+(speed/35)));
		 this->setHeight(this->getHeight()*(1 + (speed / 35)));
	 }
	 else {
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
 }

 bool Attack::beenHit(WorldObj* o) {
	 for (auto i = hitObjs.begin(); i != hitObjs.end(); ++i) {
		 if (*i == o) return true;
	 }
	 return false;
 }

 