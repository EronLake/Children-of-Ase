#pragma once

#include "stdafx.h"

#include <cstdint>

#include "LivingObj.h"

class Attack: public WorldObj
{
  public:

  Attack();
  Attack(float x, float y, bool col);// , int d);
  ~Attack() = default;

  int getDmg() { return this->dmg; };
  int getDuration() { return this->duration; };
  float getSpeed() { return this->speed; };
  bool getDestroy() { return this->destroyOnCollision; };

  int getCoolDown() { return this->cooldown; };
  int getPause() { return this->pause; };
  bool getKeep() { return this->keep; };
  vector<WorldObj*> getHits() { return this->hitObjs; };

  void setDmg(int d) { this->dmg = d; };
  void setDuration(int d) { this->duration = d; };
  bool updateDuration();
  void setSpeed(float s) { this->speed = s; };
  void setDestroy(bool d) { this->destroyOnCollision = d; };
  
  void setCoolDown(int c) { this->cooldown = c; };
  void setPause(int p) { this->pause = p; };
  void updatePause() { if(this->pause > 0) --pause; };
  void setKeep(bool k) { this->keep = k; };
  void addHit(WorldObj* o) { this->hitObjs.push_back(o); };
  bool beenHit(WorldObj* o);
  void Hit(LivingObj *target);

  void move();

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
  
  int cooldown;
  int pause;
  bool keep;
  vector<WorldObj*> hitObjs;
};
