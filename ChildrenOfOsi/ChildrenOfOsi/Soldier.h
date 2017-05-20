#pragma once

#include <cmath>

#include "Attack.h"
#include "Containers.h"
#include "NPC.h"

class Party;

class Soldier: public NPC
{
  public:
  Party *party;

  Attack* melee;
  vector<Attack*> attackTypes;
  unordered_map<Attack*, int> cooldownMap;

  Soldier() = default;
  Soldier(float x, float y, bool col);
  Soldier(Vector2f p_topLeft, float p_width, float p_height);
  ~Soldier() = default;

  int getInstances() { return instances; };

  Party* getParty() { return party; };
  bool getInCombat() { return inCombat; };
  bool getEvade() { return evade; };
  bool getHold() { return holdPos; };
  bool getPatrol() { return patrol; };
  bool is_killable() { return killable; };
  bool getSwingLeft() { return swingLeft; };
  bool getCombo();

  static const int ase_multiplier=10;
  static const int stamina_multiplier = 10;

  bool getCool();
  bool getCool(int c);
  int timeCD() { return this->cdTime; };
  int getStamina() { return (this->stamina/ stamina_multiplier); };
  int getMaxStamina() { return (this->maxStamina/ stamina_multiplier); }
  int getAse() { return (this->ase/ ase_multiplier); };
  int getMaxAse() { return (this->maxAse/ ase_multiplier); }
  int getAttackIndex(Attack* atk);
  bool get_incapacitated() { return incapacitated; };

 /* bool isAllyOf(Soldier *);
  bool isAllyOf(Party *);
  bool isEnemyOf(Soldier  *);
  bool isEnemyOf(Party *);*/

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
  void set_killable(bool k) { this->killable = k; };
  void setAggroRange(std::size_t range) { this->aggroRange = min(range, this->pursuitRange); }
  void setPursuitRange(std::size_t range) { this->pursuitRange = max(range, this->aggroRange); }

  void setStamina(int s) { this->stamina=(s*stamina_multiplier); };
  void setMaxStamina(int s) { this->maxStamina = (s*stamina_multiplier); };
  void setAse(int a) { this->ase = (a*ase_multiplier); };
  void setMaxAse(int a) { this->maxAse = (a*ase_multiplier); };
  void set_creator_of_melee() { this->melee->set_creator(this); };

  void flipSwing() { this->swingLeft = !swingLeft; };
  void meleeAttack();
  void addAttackType(Attack* a);
  void newAttack(int i, Attack* a);
  bool hasAttacks();
  Attack * nextAttack();

  void updateCD();
  void resetCD();
  void resetCD(int c);

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

  void set_action_destination(Vector2f v) { action_destination=v; };
  Vector2f get_action_destination() { return action_destination; };

  virtual void defeat(int t);
  virtual void capacitate(int t);
  virtual void incapacitate(int t);
  virtual void kill();

  int get_warning() { return warning; };
  void start_warning() { warning=400; };

  float get_max_dist_act() { return max_dist_action; };
  void set_max_dist_act(float f) { max_dist_action = f; };

  private:

  static constexpr std::size_t DEFAULT_AGGRO_RANGE = 200;
  static constexpr std::size_t DEFAULT_PURSUIT_RANGE = 500;

  //Party *party;
  int instances;

  bool inCombat;
  bool evade;
  bool holdPos;
  bool patrol;
  bool killable;
  bool incapacitated;
  std::size_t aggroRange;
  std::size_t pursuitRange;

  int cdTime;
  int down_time;
  int warning;
  int stamina;
  int maxStamina;
  int ase;
  int maxAse;
  bool swingLeft;
  
  std::string key;
  std::string atkey;

  vector<Attack*> currentAttacks;

  int evasionRadius = 225;
  Vector2f combatMoveDestination;
  Rectangle* evasionBound;

  bool targetIsWithinRange(Rectangle* _bound);

  Soldier* currentEnemy;
  Soldier* currentLeader;

  Vector2f action_destination;
  float max_dist_action;
};

