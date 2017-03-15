#pragma once

#include <cstdint>
#include <vector>

#include "common.h"

#include "Alliance.h"
#include "Player.h"
#include "Soldier.h"

class Party
{
  public:

  static constexpr int MODE_IDLE = 0;
  static constexpr int MODE_ATTACK = 1;
  static constexpr int MODE_DEFEND = 2;
  static constexpr int MODE_PATROL = 3;
  static constexpr int MODE_FLEE = 4;

  Party() = default;
  ~Party() = default;

  Alliance * getAlliance() const { return this->faction; }
  Soldier * getLeader() const { return this->leader; }
  vector<Soldier *>& getMembers() { return members; }
  int getMode() const { return this->mode; }

  void setAlliance(Alliance *a) { this->faction = a; }
  void setLeader(Soldier *);
  void addToParty(Soldier *, bool);
  void removeSoldier(Soldier *);
  void setMode(int);

  private:

  Alliance *faction; // LOL
  vector<Soldier *> members;
  Soldier *leader;
  int mode;
};

