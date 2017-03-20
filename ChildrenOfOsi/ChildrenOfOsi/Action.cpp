#include "stdafx.h"
#include "Action.h"
#include "Conditions.h"
#include "ActionExecFunctions.h"


Action::Action()
{
};

Action::Action(Hero* _owner, Hero* _receiver, Hero* _doer, int _utility, int _why, std::string _name, std::string _exe_name)
{
	owner = _owner;
	receiver = _receiver;
	doer = _doer;
	utility = _utility;
	why = _why;
	recieverName = receiver->name;
	name = _name;
	execute_ptr  = ActionExecFunctions::ActionExecMap[_exe_name];
};


Action::~Action()
{
};

void Action::applyUtiliites(bool ifsucc)
{
	if (ifsucc == true) 
	{
		for (int i = 0; i < succ_postconds.size(); i++)
		{
			if (succ_postconds[i]->get_type() =="relationship")
			{
				succ_postconds[i]->apply_utility(doer,receiver);
		}
			else
			{
				succ_postconds[i]->apply_utility();
	}
			
		}
	}
	else
	{
		for (int i = 0; i < fail_postconds.size(); i++)
		{
			if (fail_postconds[i]->get_type() == "relationship")
			{
				fail_postconds[i]->apply_utility(doer,receiver);
			}
			else 
		{
				fail_postconds[i]->apply_utility();
			}
			
		}
	}
	
}

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
	//std::////cout << "HERE 2.5" << endl;*/
	return needs;
}

int Action::exeAction() {
	/*
	vector<std::string> check = preConditionsNeeded(doer, receiver);
	if (check.empty()) {
		int tmp;
		for (int i = 0; i < succ_postconds.size(); i++) {
			if (succ_postconds[i]->rel_type == 0) {
				//doer->rel[receiver->name]->addAffinity(i->second);
			}
			else if (i->first.compare("not") == 0) {
				//doer->rel[receiver->name]->addNotoriety(i->second);
			}
			else if (i->first.compare("str") == 0) {
				//doer->rel[receiver->name]->addStrength(i->second);
			}
		}
		return 1;
	}
	*/
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