#include "stdafx.h"
#include "Action.h"
#include "Conditions.h"


Action::Action()
{
};


Action::~Action()
{
};

vector<std::string> Action::preConditionsNeeded(Hero* o, Hero* h) {
	vector<std::string> needs;/*
	owner = o;
	int tmp;
	for (auto i = preconds.begin(); i != preconds.end(); ++i) {
		if (i->first.compare("affAbove") == 0) {
			tmp = i->second - owner->rel[h->name]->getAffinity();
			if (tmp>0) {
				needs.push_back("affAbove");
			}
		}
		else if (i->first.compare("affBelow") == 0) {
			tmp = i->second - owner->rel[h->name]->getAffinity();
			if (tmp<0) {
				needs.push_back("affBelow");
			}
		}
		else if (i->first.compare("notAbove") == 0) {
			tmp = i->second - owner->rel[h->name]->getNotoriety();
			if (tmp>0) {
				needs.push_back("notAbove");
			}
		}
		else if (i->first.compare("notBelow") == 0) {
			tmp = i->second - owner->rel[h->name]->getNotoriety();
			if (tmp<0) {
				needs.push_back("notBelow");
			}
		}
		else if (i->first.compare("strAbove") == 0) {
			tmp = i->second - owner->rel[h->name]->getStrength();
			if (tmp>0) {
				needs.push_back("strAbove");
			}
		}
		else if (i->first.compare("strBelow") == 0) {
			tmp = i->second - owner->rel[h->name]->getStrength();
			if (tmp<0) {
				needs.push_back("strBelow");
			}
		}
	}
	std::cout << "HERE 2.5" << endl;*/
	return needs;
}

int Action::exeAction() {
	vector<std::string> check = preConditionsNeeded(doer, receiver);
	if (check.empty()) {
		int tmp;
		for (auto i = postconds.begin(); i != postconds.end(); ++i) {
			if (i->first.compare("aff") == 0) {
//				doer->rel[receiver->name]->addAffinity(i->second);
			}
			else if (i->first.compare("not") == 0) {
//				doer->rel[receiver->name]->addNotoriety(i->second);
			}
			else if (i->first.compare("str") == 0) {
//				doer->rel[receiver->name]->addStrength(i->second);
			}
		}
		return 1;
	}
	return 0;
}
void Action::setMultipliers(int a, int k, int h, int p, int r, int e, int g) {
	multipliers = new Personality();
	multipliers->setAggression(a);
	multipliers->setKindness(k);
	multipliers->setHonor(h);
	multipliers->setPride(p);
	multipliers->setRecklessness(r);
	multipliers->setExtroversion(e);
	multipliers->setGreed(g);
};

bool Action::operator==(const Action a) const
{
	if (a.name == name && a.receiver == receiver && a.doer == doer) {
		return true;
	}
	return false;
}