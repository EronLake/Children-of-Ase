#include "stdafx.h"

#include "Party.h"

vector<Party*> Party::partiesWorld;
Party* Party::grave=new Party();

/**
 * Creates a new party with no alliegances, no leader, and no members.
 */
Party::Party() : faction(nullptr), leader(nullptr), target(nullptr), mode(Party::MODE_IDLE), perm(false) { Party::partiesWorld.push_back(this); }

/**
 * Creates a new party with alliegance to the given faction, but no members nor
 * any leader.
 */
Party::Party(Alliance *a) : faction(a), leader(nullptr), target(nullptr), mode(Party::MODE_IDLE), perm(false) { Party::partiesWorld.push_back(this); }

/**
 * Creates a new party with the given leader, as a part of no faction.
 */
Party::Party(Soldier *leader) : faction(nullptr), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
  partiesWorld.push_back(this);
  perm = false;
}

/**
 * Creates a new party as a part of the specified alliance and with the given
 * leader. The leader will be the only initial member of this party.
 */
Party::Party(Alliance *a, Soldier *leader) : faction(a), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
  partiesWorld.push_back(this);
  perm = false;
}

/**
 * Creates a new party as a part of the specified alliance and with the given
 * leader and additional members. Note that if the vector of additional members
 * contains the leader, they will be added twice.
 */
Party::Party(Alliance *a, Soldier *leader, const vector<Soldier *>& members) : faction(a), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
	for (auto& member : members) {
    this->addToParty(member, false);
  }
  partiesWorld.push_back(this);
  perm = false;
}

/**
 * Returns whether the given soldier is an ally of this party.
 */
/*bool Party::isAllyOf(Soldier *s)
{
  return this->faction == s->getParty()->getAlliance();
}*/

/**
 * Returns whether the given party is an ally of this one.
 */
/*bool Party::isAllyOf(Party *p)
{
  return this->faction == p->faction;
}*/

/**
 * Returns whether the given soldier is an enemy of this party.
 */
/*bool Party::isEnemyOf(Soldier *s)
{
  return this->faction != s->getParty()->getAlliance();
}*/

/**
 * Returns whether the given party is an eney of this one.
 */
/*bool Party::isEnemyOf(Party *p)
{
  return this->faction != p->faction;
}*/

/**
 * Adds the given solider to this party, and sets them as the new leader if
 * specified, or if there are no other members in the party.
 */
void Party::addToParty(Soldier* s, bool isLeader)
{
	if (s != nullptr) {
		if (isLeader || members.size() == 0 || leader->getType()<s->getType()) {
      members.insert(members.begin(), s);
      this->leader = s;
      s->setParty(this);
    }
    else {
      this->members.push_back(s);
      s->setParty(this);
    }
  }
	updateFollowers();
}

void Party::add_party_to_party(Party* s) {
	vector<Soldier*> m=s->getMembers();
	for (auto i = m.begin(); i != m.end(); ++i) {
		s->removeSoldier(*i,false);
		addToParty(*i,false);
	}
}

/**
 * Removes the specified soldier from this party. If, for some reason, the
 * soldier has duplicate references in this party, all such duplicates will be
 * removed as well.
 */
void Party::removeSoldier(Soldier* s, bool b)
{
	////cout << ""
	// First find the solider in the members list
	vector<Soldier*>::iterator s_itor = find(members.begin(), members.end(), s);
	// If can't find Solder s, simply return
	if (s_itor == members.end()) {
		return;
	}
	// Get the enemy's party

	if (s->getCurrentEnemy() != nullptr) {
		// Set the enemy's party mode to be Idle so that every soldier in that party is now Idle. We might want each member of a party to have different enemies later.
		// The optimal way is to say: for each soldier, if its enemy is soldier s, set its state to Idle.
		if (s->getCurrentEnemy()->getParty() != nullptr) {
			auto tempP = s->getCurrentEnemy()->getParty();
			tempP->setMode(Party::MODE_IDLE);
		}
	}

	// Update Solder s
	s->setCurrentEnemy(nullptr);
	s->setInCombat(false);
	

	// Check whether Soldier s is the leader; handle the removal accordingly
	if (s == leader) {
		leader = nullptr;
  members.erase(std::remove(members.begin(), members.end(), s), members.end());
		// Check if member list is empty
		if (!members.empty()) {
			leader = *(members.begin());
		}
	}
	else {
		members.erase(std::remove(members.begin(), members.end(), s), members.end());
	}
  
	// Update Soldier s's party status
	//cout << "SIZE OF PARTY WITH OBJ REMOVED IS " << s->getParty()->getMembers().size() << endl;
	if (b)s->setParty(new Party(s));
	if (members.size() != 0) {
		updateFollowers();
	}


	////cout << "SIZE OF THE PARTY IS ********** " << members.size() << endl;
	//members.erase(std::remove(members.begin(), members.end(), s), members.end());
	////cout << "SUCCESFULLY GOTTEN PAST THE REMOVE SOLDIER STATEMENT*************************" << endl;

  //for enemy soldier's party, we need to remove s's party from their list of party if its emptys
  //////cout << "Enemy's enemy: " << s->getCurrentEnemy()->getCurrentEnemy() << endl;

	//if (s->getCurrentEnemy() != nullptr) {
	//	s->getCurrentEnemy()->setCurrentEnemy(nullptr);
	//	s->getCurrentEnemy()->setInCombat(false);
	//	s->getCurrentEnemy()->setEvade(false);
	//	s->getCurrentEnemy()->setHold(false);
	//}
	//s->setCurrentEnemy(nullptr);

	//if (members.empty()) {
	//	//s->getCurrentEnemy()->getParty()->setMode(Party::MODE_IDLE);
	//	leader = nullptr;
	//}
	//else
	//	if (s == leader) {
	//		leader = *(members.begin());
	//	}


  /*for(auto& i = this->members.begin(); i != this->members.end(); ++i) {
    if(*i == s) {
    this->members.erase(i);
    s->setParty(nullptr);
    if(leader == s) {
      leader = *members.begin();
    }
    }
  }*/
}

/**
 * Clears this party of all members, also leaving it leaderless.
 */
void Party::clear()
{
  this->members.clear();
  this->leader = nullptr;
}

/**
 * Sets this party's leader to the specified member, provided that the soldier
 * specified is already a member of this party. If they are not, returns without
 * making any changes.
 */
void Party::setLeader(Soldier* s)
{
	for (auto i = members.begin(); i != members.end(); ++i) {
		if (*i == s) {
      leader = s;
      break;
    }
  }
	updateFollowers();
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
  switch (m) {
  case Party::MODE_IDLE: 
		  for (auto& member : this->members) {
			  member->setHold(false);
		  }
		  default_def_rad();
		  break;
  case Party::MODE_ATTACK:
		  for (auto& member : this->members) {
			  member->setHold(false);
		  }
		  default_def_rad();
		  break;
  case Party::MODE_DEFEND:
		  for (auto& member : this->members) {
			  member->setHold(true);
		  }
		  break;
  case Party::MODE_PATROL:
		  for (auto& member : this->members) {
			  patrol_point = 0;
			  member->setHold(false);
		  }
		  default_def_rad();
		  break;
  case Party::MODE_FLEE:
		  for (auto& member : this->members) {
			  member->setHold(false);
			  member->setInCombat(false);
			  member->destination = member->getParty()->get_home();
			  member->waypoint = member->getParty()->get_home();
		  }
		  default_def_rad();
		  break;
  }
}

void Party::updateFollowers()
{
  Soldier* prev = nullptr;
	for (int i = members.size()-1; i > 0; i--) {
		members[i]->setCurrentLeader(members[0]);//members[floor((i-1)/2)]);
  }
	if (members.size()!=0)members[0]->setCurrentLeader(nullptr);
}

void Party::findEnemy()
{

}

void Party::update()
{}

Vector2f Party::get_current_patrol_loc(Vector2f n) {
	if (dist_location_to_location(n, patrol_route[patrol_point]) < 10) {
		patrol_point++;
		if (patrol_point >= patrol_route.size())patrol_point = 0;
	}
	return patrol_route[patrol_point];
}

float Party::dist_location_to_location(Vector2f n, Vector2f loc) {
	float a = (n.getXloc() - loc.getXloc());
	float b = (n.getYloc() - loc.getYloc());
	float c = sqrt(a*a + b*b);
	return c;
}

void Party::default_def_rad() {
	defend_rad = (members.size()*50);
}

void Party::down_member(Soldier* s) {
	for (auto i = members.begin(); i != members.end(); ++i) {
		if (*i == s) {
			downed_members.push_back(s);
			if (leader == s){
				if (mode != MODE_DEFEND) {
					set_defend(s->getLoc());
					setMode(MODE_DEFEND);
				}
			}
			break;
		}
	}
}

void Party::up_member(Soldier* s) {
	downed_members.erase(std::remove(downed_members.begin(), downed_members.end(), s), downed_members.end());
}

void Party::set_in_combat(bool b) {
	if (!b)currentEnemies.clear();
	//if (!b)curr_fight=nullptr;
	for (auto it = members.begin(); it != members.end(); ++it) {
		(*it)->setInCombat(b);
		if (!b)(*it)->setCurrentEnemy(nullptr);
	}
}

void Party::set_in_duel() {
	for (auto it = members.begin(); it != members.end(); ++it) {
		if (leader != (*it)) {
			(*it)->setInCombat(false);
			(*it)->defeat();
		}
		else {
			(*it)->setInCombat(true);
		}
	}
}

void Party::set_killable(bool b) {
	for (auto it = members.begin(); it != members.end();++it) {
		if (b) {
			if ((*it)->getType()<WorldObj::TYPE_HERO)(*it)->set_killable(b);
		}
		else {
			(*it)->set_killable(b);
		}
	}
}

void Party::capacitate_all(int t) {
	for (auto it = members.begin(); it != members.end(); ++it) {
		(*it)->capacitate(t);
	}
}