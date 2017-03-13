#include "stdafx.h"
#include "Party.h"


Party::Party()
{
}


Party::~Party()
{
}

void Party::addToParty(Soldier* s, bool lead) {
	members.push_back(s);
	if (lead)leader = s;
}

void Party::removeFromParty(Soldier* s) {
	for (auto i = members.begin(); i != members.end(); ++i) {
		if (*i == s) {
			members.erase(i);
			if (leader == s) {
				leader = *members.begin();
			}
		}
	}
	if (members.size() == 0) {
		//delete this;
	}
}

void Party::setLeader(Soldier* s) {
	for (auto i = members.begin(); i != members.end(); ++i) {
		if (*i == s) {
			leader = s;
		}
	}
}

void Party::setMode(int m) {
	mode = m;
	if (mode == 0) {
		for (int i = 0; i < members.size(); i++) {
			members[i]->setInCombat(false);
			members[i]->setEvade(false);
			members[i]->setHold(false);
		}
	} else if (mode == 1) {
		for (int i = 0; i < members.size(); i++) {
			members[i]->setInCombat(true);
			members[i]->setEvade(false);
			members[i]->setHold(false);
		}
	} else if (mode == 2) {
		for (int i = 0; i < members.size(); i++) {
			members[i]->setInCombat(true);
			members[i]->setHold(true);
			members[i]->setEvade(false);
		}
	} else if (mode == 3) {
		for (int i = 0; i < members.size(); i++) {
			members[i]->setInCombat(false);
			members[i]->setHold(false);
			members[i]->setEvade(false);
		}
	}
	else if (mode == 4) {
		for (int i = 0; i < members.size(); i++) {
			members[i]->setInCombat(false);
			members[i]->setHold(false);
			members[i]->setEvade(true);
		}
	}
}
