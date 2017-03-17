#pragma once

#include <cmath>

#include "Attack.h"
#include "Containers.h"
#include "NPC.h"

class Party;

class Soldier: public NPC
{
  public:

  Attack* melee;
  vector<Attack*> attackTypes;
  unordered_map<Attack*, int> cooldownMap;

  Soldier() = default;
  Soldier(float x, float y, bool col);
  Soldier(Vector2f p_topLeft, float p_width, float p_height);
  ~Soldier() = default;

  int getInstances() { return instances; };

  Party * getParty() { return party; };
  bool getInCombat() { return inCombat; };
  bool getEvade() { return evade; };
  bool getHold() { return holdPos; };
  bool getPatrol() { return patrol; };
  bool getSwingLeft() { return swingLeft; };
  bool getCombo();

  bool getCool();
  bool getCool(int c);
  int timeCD() { return this->cdTime; };
  int getStamina() { return this->stamina; };
  int getMaxStamina() { return this->maxStamina; }
  int getAse() { return this->ase; };
  int getMaxAse() { return this->maxAse; }
  int getAttackIndex(Attack* atk);

  bool isAllyOf(Soldier *);
  bool isAllyOf(Party *);
  bool isEnemyOf(Soldier  *);
  bool isEnemyOf(Party *);

  std::size_t getAggroRange() { return this->aggroRange; }
  std::size_t getPursuitRange() { return this->pursuitRange; }
  bool isInAggroRangeOf(WorldObj *);
  bool isInAggroRangeOf(Party *);
  bool isInPursuitRangeOf(WorldObj *);
  bool isInPursuitRangeOf(Party *);

  void setParty(Party* p) { this->party = p; };
  void setInCombat(bool c) { this->inCombat = c; };
  void setEvade(bool e) { this->evade = e; };
  void setHold(bool h) { this->holdPos = h; };
  void setPatrol(bool p) { this->patrol = p; };

  void setStamina(int s) { this->stamina=s; };
  void setMaxStamina(int s) { this->maxStamina = s; };
  void setAse(int a) { this->ase = a; };
  void setMaxAse(int a) { this->maxAse = a; };
  void flipSwing() { this->swingLeft = !swingLeft; };

  void meleeAttack();
  void addAttackType(Attack* a);
  void newAttack(int i, Attack* a);
  bool hasAttacks();
  Attack * nextAttack();

  void updateCD();
  void resetCD();
  void resetCD(int c);
  
  virtual void defeat();

  std::string getKey() { return key; };
  std::string getAtKey() { return atkey = "Soldier" + std::to_string(getID()) + "_" + std::to_string(attackTypes.size()) + "_" + std::to_string(instances); };

  vector<Attack*> getCurrentAttacks() { return currentAttacks; };

  private:

  Party *party;
  int instances;

  bool inCombat;
  bool evade;
  bool holdPos;
  bool patrol;
  std::size_t aggroRange;
  std::size_t pursuitRange;

  int cdTime;
  int stamina;
  int maxStamina;
  int ase;
  int maxAse;
  bool swingLeft;
  
  std::string key;
  std::string atkey;

  vector<Attack*> currentAttacks;
};

