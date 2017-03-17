#include "stdafx.h"

#include "Party.h"

/**
 * Creates a new party as a part of the specified alliance and with the given
 * leader and additional members. Note that if the vector of additional members
 * contains the leader, they will be added twice.
 */
Party::Party(Alliance *a, Soldier *leader, const vector<Soldier *>& members): faction(a), leader(leader)
{
  for(auto& member : members) {
    this->addToParty(member, false);
  }
}

bool Party::isAllyOf(Soldier *s) { return this->faction == s->getParty()->getAlliance(); }
bool Party::isAllyOf(Party *p) { return this->faction == p->faction; }
bool Party::isEnemyOf(Soldier *s) { return this->faction != s->getParty()->getAlliance(); }
bool Party::isEnemyOf(Party *p) { return this->faction != p->faction; }

/**
 * Adds the given solider to this party, and sets them as the new leader if
 * specified, or if there are no other members in the party.
 */
void Party::addToParty(Soldier* s, bool isLeader)
{
  if (isLeader || members.size() == 0) {
	  members.insert(members.begin(), s);
	  this->leader = s;
  }
  else {
	  members.push_back(s);
  }
}

/**
 * Removes the specified soldier from this party. If, for some reason, the
 * soldier has duplicate references in this party, all such duplicates will be
 * removed as well.
 */
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

/**
 * Sets this party's leader to the specified member, provided that the soldier
 * specified is already a member of this party. If they are not, returns without
 * making any changes.
 */
void Party::setLeader(Soldier* s)
{
  for(auto i = members.begin(); i != members.end(); ++i) {
    if(*i == s) {
      leader = s;
    }
  }
}

/**
 * Changes the combat mode of all members of this party to the one specified,
 * given it is valid. If the mode is not recognized, returns without making any
 * changes. Accepted combat modes are Party::MODE_IDLE, Party::MODE_ATTACK,
 * Party::MODE_DEFEND, Party::MODE_PATROL, and Party::MODE_FLEE.
 */
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
