#pragma once
#include "NPC.h"
#include "stdafx.h"
#include "Attack.h"
#include "Containers.h"

class Party;

class Soldier:
  public NPC
{
  public:

  Attack* melee;
  vector<Attack*>attackTypes;
  unordered_map<Attack*, int> cooldownMap;

  Soldier();
  Soldier(float x, float y, bool col);
  Soldier(Vector2f p_topLeft, float p_width, float p_height);
  ~Soldier();

  Party* getParty() { return party; };
  int getInstances() { return instances; };

  bool getInCombat() { return inCombat; };
  bool getEvade() { return evade; };
  bool getHold() { return holdPos; };
  bool getPatrol() { return patrol; };

  bool getCool() { return this->cdTime == 0; };
  bool getCool(int c) { return (this->cdTime == 0 && cooldownMap[attackTypes[c]] == 0); };
  int timeCD() { return cdTime; };

  void setInCombat(bool c) { inCombat = c; };
  void setEvade(bool e) { evade = e; };
  void setHold(bool h) { holdPos = h; };
  void setPatrol(bool p) { patrol = p; };
  
  void meleeAttack();
  void addAttackType(Attack* a);
  void newAttack(int i, Attack* a);
  Attack * nextAttack();

  void updateCD();
  void resetCD(int c);
  
  void setParty(Party* p) { party = p; };
  std::string getKey() { return key; };
  std::string getAtKey() { return atkey = "Soldier" + std::to_string(getID()) + "_" + std::to_string(attackTypes.size()) + "_" + std::to_string(instances); };

  private:

  Party* party;
  int instances;

  bool inCombat;
  bool evade;
  bool holdPos;
  bool patrol;

  int cdTime;
  
  std::string key;
  std::string atkey;

  bool hasAttacks();
};

