#include "stdafx.h"
#include "Party.h"


Party::Party()
{
}


Party::~Party()
{
}

void Party::addToParty(Soldier* s, bool lead) {
	group.push_back(s);
	if (lead)leader = s;
}

void Party::removeFromParty(Soldier* s) {
	for (auto i = group.begin(); i != group.end(); ++i) {
		if (*i == s) {
			group.erase(i);
			if (leader == s) {
				leader = *group.begin();
			}
		}
	}
	if (group.size() == 0) {
		//delete this;
	}
}

void Party::setLeader(Soldier* s) {
	for (auto i = group.begin(); i != group.end(); ++i) {
		if (*i == s) {
			leader = s;
		}
	}
}

void Party::setMode(int m) {
	mode = m;
	if (mode == 0) {
		for (int i = 0; i < group.size(); i++) {
			group[i]->setInCombat(false);
			group[i]->setEvade(false);
			group[i]->setHold(false);
		}
	} else if (mode == 1) {
		for (int i = 0; i < group.size(); i++) {
			group[i]->setInCombat(true);
			group[i]->setEvade(false);
			group[i]->setHold(false);
		}
	} else if (mode == 2) {
		for (int i = 0; i < group.size(); i++) {
			group[i]->setInCombat(true);
			group[i]->setHold(true);
			group[i]->setEvade(false);
		}
	} else if (mode == 3) {
		for (int i = 0; i < group.size(); i++) {
			group[i]->setInCombat(false);
			group[i]->setHold(false);
			group[i]->setEvade(false);
		}
	}
	else if (mode == 4) {
		for (int i = 0; i < group.size(); i++) {
			group[i]->setInCombat(false);
			group[i]->setHold(false);
			group[i]->setEvade(true);
		}
	}
}
