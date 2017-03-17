#pragma once

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
  int timeCD() { return cdTime; };
  int getStamina() { return stamina; };
  int getAse() { return ase; };
  int getAttackIndex(Attack* atk);

  bool isAllyOf(Soldier *);
  bool isAllyOf(Party *);
  bool isEnemyOf(Soldier  *);
  bool isEnemyOf(Party *);

  void setParty(Party* p) { party = p; };
  void setInCombat(bool c) { inCombat = c; };
  void setEvade(bool e) { evade = e; };
  void setHold(bool h) { holdPos = h; };
  void setPatrol(bool p) { patrol = p; };
  void setStamina(int s) { stamina=s; };
  void setAse(int a) { ase = a; };
  void setMaxStamina(int s) { maxStamina = s; };
  void setMaxAse(int a) { maxAse = a; };
  void flipSwing() { swingLeft = !swingLeft; };

  void meleeAttack();
  void addAttackType(Attack* a);
  void newAttack(int i, Attack* a);
  Attack * nextAttack();

  void updateCD();
  void resetCD();
  void resetCD(int c);
  
  virtual void defeat();

  std::string getKey() { return key; };
  std::string getAtKey() { return atkey = "Soldier" + std::to_string(getID()) + "_" + std::to_string(attackTypes.size()) + "_" + std::to_string(instances); };

  vector<Attack*> getCurrentAttacks() { return currentAttacks; };

  void setEvasionRadius(int _radius) { this->evasionRadius = _radius; }

  int getEvasionRadius() { return this->evasionRadius; };
  Vector2f getEvadeRange(Soldier* _enemy);
  Vector2f getCombatMoveDestination() { return this->combatMoveDestination; };
  Vector2f getStrafeLocation(Soldier* _enemy);


  Soldier* getCurrentEnemy() { return currentEnemy; };
  void setCurrentEnemy(Soldier* p_enemy) { currentEnemy = p_enemy; };

  Soldier* getCurrentLeader() { return currentLeader; };
  void setCurrentLeader(Soldier* p_leader) { currentLeader = p_leader; };

  private:

  Party* party;
  int instances;

  bool inCombat;
  bool evade;
  bool holdPos;
  bool patrol;

  int cdTime;
  int stamina;
  int maxStamina;
  int ase;
  int maxAse;
  bool swingLeft;
  
  std::string key;
  std::string atkey;

  bool hasAttacks();
  vector<Attack*> currentAttacks;

  int evasionRadius = 225;
  Vector2f combatMoveDestination;
  Rectangle* evasionBound;

  bool targetIsWithinRange(Rectangle* _bound);

  Soldier* currentEnemy;
  Soldier* currentLeader;
};

