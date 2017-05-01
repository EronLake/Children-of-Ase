#include "stdafx.h"

#include "Soldier.h"

#include "Party.h"
#include "Vector2f.h"

using namespace std;

Soldier::Soldier(float x, float y, bool col): NPC(x, y, col),
key(string("Soldier") + std::to_string(getID()) + "_0"), party(nullptr), instances(0),
inCombat(false), evade(false), holdPos(false), patrol(false),
stamina(100), maxStamina(100), ase(0), maxAse(0),
aggroRange(Soldier::DEFAULT_AGGRO_RANGE),
pursuitRange(Soldier::DEFAULT_PURSUIT_RANGE),
cdTime(0), swingLeft(true)
{
  evasionBound = new Rectangle();
  swingLeft = true;
  setType(WorldObj::TYPE_SOLDIER);
  currentEnemy = nullptr;
  currentLeader = nullptr;
  party = nullptr;
  action_destination = Vector2f(NULL, NULL);
  killable = true;
  incapacitated = false;
  down_time = 0;
  warning = 0;
  ase = 100;
  maxAse = 100;
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height): NPC(p_topLeft, p_width, p_height),
key(string("Soldier") + std::to_string(getID()) + "_0"), party(nullptr), instances(0),
inCombat(false), evade(false), holdPos(false), patrol(false),
stamina(100), maxStamina(100), ase(0), maxAse(0),
aggroRange(Soldier::DEFAULT_AGGRO_RANGE),
pursuitRange(Soldier::DEFAULT_PURSUIT_RANGE),
cdTime(0), swingLeft(true)
{
  swingLeft = true;
  evasionBound = new Rectangle();
  setType(WorldObj::TYPE_SOLDIER);
  currentEnemy = nullptr;
  currentLeader = nullptr;
  party = nullptr;
  action_destination = Vector2f(NULL, NULL);
  killable = true;
  incapacitated = false;
  down_time = 0;
  warning = 0;
  ase = 100;
  maxAse = 100;
}

void Soldier::addAttackType(Attack* a)
{
  attackTypes.push_back(a);
  cooldownMap[a] = a->getCoolDown();
}

void Soldier::newAttack(int i, Attack* a)
{
  Attack* p = a;
  *p = *attackTypes[i];

  float w = attackTypes[i]->getWidth();
  if(w == 0)w = body[0].getWidth();
  float h = attackTypes[i]->getHeight();
  if(h == 0)h = body[0].getHeight();
  float x = body[0].getX();
  float y = body[0].getY();
  int bd = attackTypes[i]->getBaseDir();
  switch (getDirection()) {
  case WorldObj::DIRECTION_UP:
		  y = y - (h);
		  if (!attackTypes[i]->getCanCancel())p->sprite.setTexture(p->sprite.up);
		  if (bd == 4)x += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  if (bd == 6)x -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  break;
  case WorldObj::DIRECTION_DOWN:
		  y = y + (h);
		  if (!attackTypes[i]->getCanCancel())p->sprite.setTexture(p->sprite.down);
		  if (bd == 4)x -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  if (bd == 6)x += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  break;
  case WorldObj::DIRECTION_LEFT:
		  x = x - (w);
		  if (!attackTypes[i]->getCanCancel())p->sprite.setTexture(p->sprite.left);
		  if (bd == 4)y -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  if (bd == 6)y += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  break;
  case WorldObj::DIRECTION_RIGHT:
		  x = x + (w);
		  if (!attackTypes[i]->getCanCancel())p->sprite.setTexture(p->sprite.right);
		  if (bd == 4)y += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  if (bd == 6)y -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 2);
		  break;
  }
  p->setX(x);
  p->setY(y);
  p->setCollision(true);
  p->addHit(this);
  p->setDmg(attackTypes[i]->getDmg());
  p->setDuration(attackTypes[i]->getDuration());
  p->setDestroy(attackTypes[i]->getDestroy());
  p->setSpeed(attackTypes[i]->getSpeed());
  p->setWidth(w);
  p->setHeight(h);
  p->setDirWithBase(getDirection(), false);
  p->setPause(attackTypes[i]->getPause());
  p->setKeep(false);
  p->set_creator(this);
  cooldownMap[attackTypes[i]] = attackTypes[i]->getCoolDown();
  cdTime = melee->getCoolDown();
  stamina -= attackTypes[i]->getStaminaCost();
  ase -= attackTypes[i]->getAseCost();
  instances++;
  if(instances == 99)instances = 0;
  currentAttacks.push_back(p);
  if(attackTypes[i]->getTurn())setDirWithBase(4, true);
}

void Soldier::meleeAttack()
{
  melee->addHit(this);
  float x = body[0].getX();
  float y = body[0].getY();
  melee->setDuration(5);
  melee->setCanCancel(true);
  if(!swingLeft) {
    melee->setBaseDir(6);
    melee->setPause(1);
  }
  else {
    melee->setBaseDir(4);
    melee->setPause(8);
  }
  switch (getDirection()) {
  case WorldObj::DIRECTION_UP:
		  y = y - (melee->getHeight() / 1.2);
		  if (swingLeft) { x += (melee->getSpeed()*melee->getDuration() / 1.2); }
		  else { x -= (melee->getSpeed()*melee->getDuration() / 1.2); }
		  break;
  case WorldObj::DIRECTION_DOWN:
		  y = y + (body[0].getHeight() / 1.2);
		  if (swingLeft) { x -= (melee->getSpeed()*melee->getDuration() / 1.2); }
		  else { x += (melee->getSpeed()*melee->getDuration() / 1.2); }
		  break;
  case WorldObj::DIRECTION_LEFT:
		  x = x - (melee->getWidth() / 1.2);
		  if (swingLeft) { y -= (melee->getSpeed()*melee->getDuration() / 1.2); }
		  else { y += (melee->getSpeed()*melee->getDuration() / 1.2); }
		  break;
  case WorldObj::DIRECTION_RIGHT:
		  x = x + (body[0].getWidth() / 1.2);
		  if (swingLeft) { y += (melee->getSpeed()*melee->getDuration() / 1.2); }
		  else { y -= (melee->getSpeed()*melee->getDuration() / 1.2); }
		  break;
  }
  melee->setDirWithBase(getDirection(), false);
  melee->setX(x);
  melee->setY(y);
  stamina -= melee->getStaminaCost();
  currentAttacks.push_back(melee);
  cdTime = melee->getCoolDown();
}

void Soldier::updateCD()
{
  if(cdTime > 0)
    --cdTime;
  else
    swingLeft = true;

  for(auto i = cooldownMap.begin(); i != cooldownMap.end(); ++i) {
    if(i->second > 0) {
      i->second--;
    }
  }
  if (incapacitated) {
	  if (down_time <= 0) {
		  this->capacitate(0);
	  }
	  else down_time--;
  }
  if (warning>0) {
	  warning--;
  }


  if(ase < maxAse)
    ++ase;
  if(stamina < maxStamina)
    ++stamina;
}


void Soldier::resetCD()
{
  cdTime = 0;
}

void Soldier::resetCD(int c)
{
  cdTime = 0;
  cooldownMap[attackTypes[c]] = 0;
}

/*
 * This function is overloaded by Hero. Acts like kill for soldiers
void Soldier::defeat()
{
  //this->getParty()->removeSoldier(this);
}*/

//this removes the soldier from the party and sets its party to null
void Soldier::defeat()
{
	if (!killable) {
		incapacitate();
	}
	else {
		kill();
	}
}

void Soldier::capacitate(int t)
{
	int prev = 0;
	if (!incapacitated)prev = this->getHealth();
	switch (t) {
	case 0:
		this->setHealth(get_max_health()/ 4);
		break;
	case 1:
		this->setHealth(get_max_health() / 2);
		break;
	case 2:
		this->setHealth((get_max_health()*3) / 4);
		break;
	case 3:
		this->setHealth(get_max_health());
		break;
	}
	if (incapacitated) {
		this->getParty()->up_member(this);
	} else if (prev > this->getHealth())this->setHealth(prev);
	incapacitated = false;
}

void Soldier::incapacitate()
{
	if (!incapacitated) {
		down_time = 900;
		incapacitated = true;
		this->getParty()->down_member(this);
	}
}

void Soldier::kill()
{
	this->getParty()->removeSoldier(this, false);
	Party::grave->addToParty(this,false);
}

/**
* Returns whether this solider has any non-melee attacks remaining.
* Returns: true if any of this solider's attacks have a non-zero cooldown,
* otherwise false
*/
bool Soldier::hasAttacks()
{
  if(this->attackTypes.empty())
    return false;
  else {
    for(auto& attackCooldown : this->cooldownMap)
      if(attackCooldown.second != 0) return true;
    return false;
  }
}

/**
 * Returns the next attack which this soldier should perform at this time.
 * Summoning abilities always take precendence over anything else. After those,
 * special abilities take precendence over the standrd melee attack, which is
 * the last resort. If every attack, even the basic melee attack, is on cooldown
 * then nullptr will be returned.
 *
 * Returns: A pointer to the next attack this solider should perform, based on
 * the cooldowns of all their abilities
*/
Attack * Soldier::nextAttack()
{
  if(!(this->hasAttacks()))
    return this->melee;
  else {
    for(auto& attack : this->attackTypes) {
      if(attack->getAttackType() == Attack::AttackTypes::SUMMONING && attack->getCoolDown() == 0) {
        return attack;
      }
    }

    for(auto& attack : this->attackTypes) {
      if(attack->getAttackType() != Attack::AttackTypes::SUMMONING && attack->getCoolDown() == 0) {
        return attack;
      }
    }

    if(this->melee->getCoolDown() == 0) return this->melee;
    else return nullptr;
  }
}

/*bool Soldier::isAllyOf(Soldier *s) { return this->party->isAllyOf(s); }
bool Soldier::isAllyOf(Party *p) { return this->party->isAllyOf(p); }
bool Soldier::isEnemyOf(Soldier *s) { return this->party->isEnemyOf(s); }
bool Soldier::isEnemyOf(Party *p) { return this->party->isEnemyOf(p); }*/

/**
 * Return whether the given world object is within the range of this soldier's
 * aggression.
 */
bool Soldier::isInAggroRangeOf(WorldObj *w)
{
  if(w == nullptr) return false;
  float distanceX = abs(this->getX() - w->getX());
  float distanceY = abs(this->getY() - w->getY());
  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
  return distance <= this->aggroRange;
}

/**
 * Returns whether the leader of the given party is within the range of this
 * soldier's aggression.
 */
bool Soldier::isInAggroRangeOf(Party *p)
{
  if(p == nullptr) return false;
  float distanceX = abs(this->getX() - p->getLeader()->getX());
  float distanceY = abs(this->getY() - p->getLeader()->getY());
  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
  return distance <= this->aggroRange;
}

/**
 * Returns whether the given world object is near enoguh for this soldier to
 * continue pursuit after it has fled.
 */
bool Soldier::isInPursuitRangeOf(WorldObj *w)
{
  if(w == nullptr) return false;
  float distanceX = abs(this->getX() - w->getX());
  float distanceY = abs(this->getY() - w->getY());
  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
  return distance <= this->pursuitRange;
}

/**
 * Returns whether the leader of the given party is near enough for this soldier
 * to continue pursuit after they have fled.
 */
bool Soldier::isInPursuitRangeOf(Party *p)
{
  if(p == nullptr) return false;
  float distanceX = abs(this->getX() - p->getLeader()->getX());
  float distanceY = abs(this->getY() - p->getLeader()->getY());
  float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
  return distance <= this->pursuitRange;
}

bool Soldier::getCool()
{
  return ((this->cdTime == 0) && (this->sprite.getLock() == false) &&
    (stamina >= melee->getStaminaCost()) && (ase >= melee->getAseCost()));
}

bool Soldier::getCool(int c)
{
  return ((this->cdTime == 0) && (cooldownMap[attackTypes[c]] == 0)
    && (this->sprite.getLock() == false) && (stamina >= attackTypes[c]->getStaminaCost())
    && (ase >= attackTypes[c]->getAseCost()));
}

int Soldier::getAttackIndex(Attack* atk)
{
  for(int i = 0; i < attackTypes.size(); i++) {
    if(attackTypes[i] == atk)return i;
  }
  return -1;
}

bool Soldier::getCombo()
{
  return (cdTime > 0 && cdTime < 5);
}


bool Soldier::targetIsWithinRange(Rectangle* _bound) {

	return (combatMoveDestination.getXloc() > _bound->getX()
		&& combatMoveDestination.getXloc() < (_bound->getX() + _bound->getWidth())
		&& combatMoveDestination.getYloc() > _bound->getY()
		&& combatMoveDestination.getYloc() < (_bound->getY() + _bound->getHeight()));
}

Vector2f Soldier::getEvadeRange(Soldier * _enemy)
{
	//gen the rectangle bound to move
	float leftBound = _enemy->getX() - _enemy->getEvasionRadius();
	evasionBound = new Rectangle(Vector2f((_enemy->getX() - _enemy->getEvasionRadius()), (_enemy->getY() - _enemy->getEvasionRadius())), 2 * _enemy->getEvasionRadius(), 2 * _enemy->getEvasionRadius());
	if (targetIsWithinRange(evasionBound)) {
		////cout << "COMBAT DESTINATION FROM EVADERANGE IS " << combatMoveDestination.getXloc() << ", " << combatMoveDestination.getYloc() << endl;
		return combatMoveDestination;
	}
	float XCoord = rand() % (int)evasionBound->getWidth() + (int)evasionBound->getX();
	float YCoord = rand() % (int)evasionBound->getHeight() + (int)evasionBound->getY();
	combatMoveDestination = Vector2f(XCoord, YCoord);

	////cout << "COMBAT DESTINATION FROM EVADERANGE IS " << combatMoveDestination.getXloc() << ", " << combatMoveDestination.getYloc() << endl;
	return combatMoveDestination;
}

Vector2f Soldier::getStrafeLocation(Soldier * _enemy)
{
	float XCoord;
	if (this->getX() < ((evasionBound->getX() + evasionBound->getWidth()) / 2)) {
		//XCoord = rand() % 50 + ((int)evasionBound->getX()+(int)evasionBound->getWidth() - 50);
		XCoord = rand() % (int)evasionBound->getWidth() + (int)evasionBound->getX();
	}
	else {
		XCoord = rand() % 50 + ((int)evasionBound->getX());
	}
	return Vector2f(XCoord, combatMoveDestination.getYloc());


}