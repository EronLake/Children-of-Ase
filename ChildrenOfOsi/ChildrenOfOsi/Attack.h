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

  int getDmg() { return dmg; };

  void setDmg(int d) { dmg = d; };

  void Hit(LivingObj *target);
  
  
  void setDuration(int d) { duration = d; };
  bool updateDuration();
  int getDuration() { return duration; };
  void setDestroy(bool d) { destroyOnCollision = d; };
  bool getDestroy() { return destroyOnCollision; };
  void setSpeed(float s) { speed = s; };
  float getSpeed() { return speed; };
  void setCoolDown(int c) { cooldown = c; };
  int getCoolDown() { return cooldown; };
  void move();
  void addHit(WorldObj* o) { hitObjs.push_back(o); };
  vector<WorldObj*> getHits() { return hitObjs; };
  void setPause(int p) { pause = p; };
  void updatePause() { if(pause > 0)pause--; };
  int getPause() { return pause; };
  void setKeep(bool k) { keep = k; };
  bool getKeep() { return keep; };
  void setTurn(int d) { turn = d; };
  int getTurn() { return turn; };

  static enum class AttackTypes: uint8_t
  {
    SPECIAL_MELEE,
    SPECIAL_PROJECTILE,
    SUMMONING
  };

  private:

  int dmg;
  int duration; // -1 will mean infinity

  bool destroyOnCollision;
  float speed;
  int cooldown;
  int pause;
  vector<WorldObj*> hitObjs;
  bool keep;
  int turn;
};
