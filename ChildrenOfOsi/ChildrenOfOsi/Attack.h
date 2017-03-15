#pragma once

#include "stdafx.h"

#include <cstdint>

#include "LivingObj.h"

class Attack: public WorldObj
{
  public:

  enum class AttackTypes: uint8_t;

  Attack();
  Attack(float x, float y, bool col);// , int d);
  ~Attack() = default;

  int getDmg() { return this->dmg; };
  int getDuration() { return this->duration; };
  float getSpeed() { return this->speed; };
  bool getDestroy() { return this->destroyOnCollision; };

  int getCoolDown() { return this->cooldown; };
  int getStaminaCost() { return this->staminaCost; };
  int getAseCost() { return this->aseCost; };
  int getPause() { return this->pause; };
  bool getKeep() { return this->keep; };
  bool getTurn() { return this->turn; };
  vector<WorldObj*> getHits() { return this->hitObjs; };
  AttackTypes getType() { return this->type; }

  void setDmg(int d) { this->dmg = d; };
  void setStaminaCost(int c) { this->staminaCost = c; };
  void setAseCost(int c) { this->aseCost=c; };
  void setDuration(int d) { this->duration = d; };
  bool updateDuration();
  void setSpeed(float s) { this->speed = s; };
  void setDestroy(bool d) { this->destroyOnCollision = d; };
  void setType(AttackTypes t) { this->type = t; }
  
  void setCoolDown(int c) { this->cooldown = c; };
  void setPause(int p) { this->pause = p; };
  void updatePause() { if(this->pause > 0) --pause; };
  void setKeep(bool k) { this->keep = k; };
  void setTurn(bool t) { this->turn=t; };
  void addHit(WorldObj* o) { this->hitObjs.push_back(o); };
  bool beenHit(WorldObj* o);
  void Hit(LivingObj *target);

  void move();

  void Attack::setNextAttack(Attack* n) { next = n; };
  Attack* Attack::getNextAttack() { return next; };


  enum class AttackTypes: uint8_t
  {
    SPECIAL_MELEE,
    SPECIAL_PROJECTILE,
    SUMMONING
  };

  private:

  int dmg;
  int duration; // -1 will mean infinity
  float speed;
  bool destroyOnCollision;
  int aseCost;
  int staminaCost;
  
  int cooldown;
  int pause;
  bool keep;
  vector<WorldObj*> hitObjs;
  Attack* next;
  bool turn;
  AttackTypes type;
};
