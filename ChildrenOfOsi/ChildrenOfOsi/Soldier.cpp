#include "stdafx.h"

#include "Soldier.h"
#include "Party.h"

using namespace std;

Soldier::Soldier() {}

Soldier::Soldier(float x, float y, bool col):NPC(x, y, col)
{
  key = "Soldier" + std::to_string(getID()) + "_0";
  cdTime = 0;
  setType(3);
  ase = 0;
  maxAse = 0;
  stamina= 100;
  maxStamina = 100;
  swingLeft = true;
}

Soldier::Soldier(Vector2f p_topLeft, float p_width, float p_height):NPC(p_topLeft, p_width, p_height)
{
  key = "Soldier" + std::to_string(getID()) + "_0";
  cdTime = 0;
  setType(3);
  ase = 0;
  maxAse = 0;
  stamina = 100;
  maxStamina = 100;
  swingLeft = true;
}

Soldier::~Soldier() {}

void Soldier::addAttackType(Attack* a)
{
  attackTypes.push_back(a);
  cooldownMap[a] = a->getCoolDown();
}

void Soldier::newAttack(int i, Attack* a)
{
  //if(cooldownMap[attackTypes[i]] == 0 && stamina>=attackTypes[i]->getStaminaCost() && ase>=attackTypes[i]->getAseCost()) {
    Attack* p = a;
    *p = *attackTypes[i];

    float w = attackTypes[i]->getWidth();
    if(w == 0)w = body[0].getWidth();
    float h = attackTypes[i]->getHeight();
    if(h == 0)h = body[0].getHeight();
    float x = body[0].getX();
    float y = body[0].getY();
    int d = getDirection();
	int bd = attackTypes[i]->getBaseDir();
    if(d == 8) {
      y = y - (attackTypes[i]->getHeight() / 1.2);
	  if (bd == 4)x += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
	  if (bd == 6)x -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
    }
    else if(d == 2) {
      y = y + (body[0].getHeight() / 1.2);
	  if (bd == 4)x -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
	  if (bd == 6)x += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
    }
    else if(d == 4) {
      x = x - (attackTypes[i]->getWidth() / 1.2);
	  if (bd == 4)y -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
	  if (bd == 6)y += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
    }
    else if(d == 6) {
      x = x + (body[0].getWidth() / 1.2);
	  if (bd == 4 )y += (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration() / 1.2);
	  if (bd == 6)y -= (attackTypes[i]->getSpeed()*attackTypes[i]->getDuration()/1.2);
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
    p->setDirWithBase(d,false);
    p->setPause(attackTypes[i]->getPause());
    p->setKeep(false);
    cooldownMap[attackTypes[i]] = attackTypes[i]->getCoolDown();
	cdTime = attackTypes[i]->getCoolDown();
	stamina -= attackTypes[i]->getStaminaCost();
	ase -= attackTypes[i]->getAseCost();
    instances++;
    if(instances == 99)instances = 0;
	currentAttacks.push_back(p);
	if (attackTypes[i]->getTurn())setDirWithBase(6,true);
  //}
}

void Soldier::meleeAttack()
{
  melee->addHit(this);
  float x = body[0].getX();
  float y = body[0].getY();
  melee->setDuration(5);
  melee->setCanCancel(true);
  int d = getDirection();
  if (!swingLeft) {
	  melee->setBaseDir(6);
	  melee->setPause(10);
  }
  else {
	  melee->setBaseDir(4);
	  melee->setPause(24);
  }
  if(d == 8) {
    y = y - (melee->getHeight()/1.2);
	if (swingLeft) { x += (melee->getSpeed()*melee->getDuration() / 1.2); }
	else { x -= (melee->getSpeed()*melee->getDuration() / 1.2); }
  }
  else if(d == 2) {
    y = y + (body[0].getHeight()/1.2);
	if (swingLeft) { x -= (melee->getSpeed()*melee->getDuration() / 1.2); }
	else { x += (melee->getSpeed()*melee->getDuration() / 1.2); }
  }
  else if(d == 4) {
    x = x - (melee->getWidth()/1.2);
	if (swingLeft) { y -= (melee->getSpeed()*melee->getDuration() / 1.2); }
	else { y += (melee->getSpeed()*melee->getDuration() / 1.2); }
  }
  else if(d == 6) {
    x = x + (body[0].getWidth()/1.2);
	if (swingLeft) { y += (melee->getSpeed()*melee->getDuration() / 1.2); }
	else { y -= (melee->getSpeed()*melee->getDuration() / 1.2); }
  }
  melee->setDirWithBase(d,false);
  melee->setX(x);
  melee->setY(y);
  currentAttacks.push_back(melee);
  cdTime = melee->getCoolDown();
}

void Soldier::updateCD()
{
	if (cdTime > 0) {
		--cdTime;
	}
	else {
		swingLeft = true;
	}
  for(auto i = cooldownMap.begin(); i != cooldownMap.end(); ++i) {
    if(i->second > 0) {
      i->second--;
    }
  }
  for (auto i = currentAttacks.begin(); i != currentAttacks.end(); ++i) {
	  if (*i == nullptr) {
		  currentAttacks.erase(i);
	  } else {
		 if((*i)->getPause() == 0 && !(*i)->getCanCancel()){
			 currentAttacks.erase(i);
		 }
	  }
  }
  if (ase < maxAse)ase++;
  if (stamina < maxStamina)stamina++;
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
/*
//this function is overloaded by Hero. Acts lik kill for soldiers
void Soldier::defeat()
{
	//this->getParty()->removeSoldier(this);
}
*/
//this removes the soldier from the party and sets its party to null
void Soldier::defeat()
{
	this->getParty()->removeSoldier(this);
	this->setParty(NULL);
}

/**
 * Returns the next attack which this soldier should perform at this time.
*/
Attack * Soldier::nextAttack()
{
  if(!(this->hasAttacks()))
    return this->melee;
  else {

    return nullptr;
  }
}

bool Soldier::getCool() { 
	return ((this->cdTime == 0) && (this->sprite.getLock() == false) && 
		(stamina >= melee->getStaminaCost()) && (ase >= melee->getAseCost()));
}

bool Soldier::getCool(int c) { 
	return ((this->cdTime == 0) && (cooldownMap[attackTypes[c]] == 0) 
		&& (this->sprite.getLock() == false) && (stamina>=attackTypes[c]->getStaminaCost())
		&& (ase>=attackTypes[c]->getAseCost()));
}

int Soldier::getAttackIndex(Attack* atk) {
	for (int i = 0; i < attackTypes.size(); i++) {
		if (attackTypes[i] == atk)return i;
	}
	return -1;
}

bool Soldier::getCombo() { 
	return (cdTime>0 && cdTime<15);
}



