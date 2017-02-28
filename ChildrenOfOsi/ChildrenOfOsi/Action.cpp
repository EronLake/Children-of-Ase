#include "stdafx.h"
#include "Action.h"


Action::Action()
{
}


Action::~Action()
{
}

vector<std::string> Action::preConditionsNeeded(Hero* o, Hero* h) {
	vector<std::string> needs;
	owner = o;
	int tmp;
	for (auto i = preconds.begin(); i != preconds.end(); ++i) {
		if (i->first.compare("affAbove") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp>0) {
				needs.push_back("affAbove");
			}
		}
		else if (i->first.compare("affBelow") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp<0) {
				needs.push_back("affBelow");
			}
		}
		else if (i->first.compare("notAbove") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp>0) {
				needs.push_back("notAbove");
			}
		}
		else if (i->first.compare("notBelow") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp<0) {
				needs.push_back("notBelow");
			}
		}
		else if (i->first.compare("strAbove") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp>0) {
				needs.push_back("strAbove");
			}
		}
		else if (i->first.compare("strBelow") == 0) {
			tmp = (i->second) - (owner->getRelation(h->getNameNum())->getAffinity());
			if (tmp<0) {
				needs.push_back("strBelow");
			}
		}
	}
	return needs;
}

int Action::exeAction() {
	vector<std::string> check = preConditionsNeeded(owner, hero);
	if (check.empty()) {
		int tmp;
		for (auto i = postconds.begin(); i != postconds.end(); ++i) {
			if (i->first.compare("aff") == 0) {
				owner->getRelation(hero->getNameNum())->addAffinity(i->second);
			}
			else if (i->first.compare("not") == 0) {
				owner->getRelation(hero->getNameNum())->addNotoriety(i->second);
			}
			else if (i->first.compare("str") == 0) {
				owner->getRelation(hero->getNameNum())->addStrength(i->second);
			}
		}
		return 1;
	}
	return 0;
}