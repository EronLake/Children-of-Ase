#pragma once

#include <cstdint>
#include <vector>

#include "common.h"
#include "Player.h"
#include "Soldier.h"

class Alliance;

class Party
{
  public:

  static constexpr int MODE_IDLE = 0;
  static constexpr int MODE_ATTACK = 1;
  static constexpr int MODE_DEFEND = 2;
  static constexpr int MODE_PATROL = 3;
  static constexpr int MODE_FLEE = 4;

  Party();
  Party(Alliance *a);
  Party(Soldier *leader);
  Party(Alliance *a, Soldier *leader);
  Party(Alliance *a, Soldier *leader, const vector<Soldier *>& members);
  ~Party() = default;
  static vector<Party*> partiesWorld;

  Alliance * getAlliance() const { return this->faction; }
  Soldier * getLeader() const { return this->leader; }
  vector<Soldier *>& getMembers() { return members; }
  int getMode() const { return this->mode; }

  bool isAllyOf(Soldier *);
  bool isAllyOf(Party *);
  bool isEnemyOf(Soldier *);
  bool isEnemyOf(Party *);

  void setAlliance(Alliance *a) { this->faction = a; }
  void setLeader(Soldier *);
  void addToParty(Soldier *, bool);
  void removeSoldier(Soldier *);
  void clear();
  void setMode(int);
  void updateFollowers();

  void findEnemy();
  void update();

  void addToCurrentEnemies(Party* p) { currentEnemies.push_back(p); };
  vector<Party*> getCurrentEnemies() { return currentEnemies; };

  private:

  Alliance* faction;
  vector<Soldier *> members;
  Soldier *leader;

  LivingObj *target;
  int mode;
  vector<Party*> currentEnemies;
};

