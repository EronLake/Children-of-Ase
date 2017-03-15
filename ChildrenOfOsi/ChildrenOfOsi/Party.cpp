#include "stdafx.h"

#include "Party.h"

void Party::addToParty(Soldier* s, bool isLeader)
{
  members.push_back(s);
  if(isLeader)
    this->leader = s;
}

void Party::removeSoldier(Soldier* s)
{
  for(auto& i = this->members.begin(); i != this->members.end(); ++i) {
    if(*i == s) {
      this->members.erase(i);
      if(leader == s) {
        leader = *members.begin();
      }
    }
  }
}

void Party::setLeader(Soldier* s)
{
  for(auto i = members.begin(); i != members.end(); ++i) {
    if(*i == s) {
      leader = s;
    }
  }
}

void Party::setMode(int m)
{
  this->mode = m;
  if(mode == Party::MODE_IDLE) {
    for(auto& member: this->members) {
      member->setInCombat(false);
      member->setEvade(false);
      member->setHold(false);
    }
  }
  else if(mode == Party::MODE_ATTACK) {
    for(auto& member : this->members) {
      member->setInCombat(true);
      member->setEvade(false);
      member->setHold(false);
    }
  }
  else if(mode == Party::MODE_DEFEND) {
    for(auto& member : this->members) {
      member->setInCombat(true);
      member->setHold(true);
      member->setEvade(false);
    }
  }
  else if(mode == Party::MODE_PATROL) {
    for(auto& member : this->members) {
      member->setInCombat(false);
      member->setHold(false);
      member->setEvade(false);
    }
  }
  else if(mode == Party::MODE_FLEE) {
    for(auto& member : this->members) {
      member->setInCombat(false);
      member->setHold(false);
      member->setEvade(true);
    }
  }
}
