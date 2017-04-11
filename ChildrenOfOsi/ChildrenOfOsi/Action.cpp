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
	if (receiver!=nullptr)recieverName = receiver->name;
	name = _name;
	execute_ptr  = ActionExecFunctions::ActionExecMap[_exe_name];

	multipliers = new Personality();
	str_mult = new Personality();
	aff_mult = new Personality();
	noto_mult = new Personality();
};


Action::~Action()
{
	delete(multipliers);
	delete(str_mult);
	delete(aff_mult);
	delete(noto_mult);
};

void Action::applyUtiliites(bool ifsucc)
{
	if (ifsucc == true) 
	{
		for (int i = 0; i < succ_postconds.size(); i++)
		{
			if (succ_postconds[i]->get_general_type() =="relationship")
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
			if (fail_postconds[i]->get_general_type() == "relationship")
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
	vector<std::string> needs;
	for (auto it = req_preconds.begin(); it != req_preconds.end(); ++it) {
		if ((*it)->get_general_type().compare("relationship")==0) {
			RelPrecon* bullshit= dynamic_cast<RelPrecon*>((*it).get());
			if (bullshit->get_cost(o, h) > 0) {
				needs.push_back((*it)->get_type());
			}
		}
		else if ((*it)->get_general_type().compare("relationship_estimate") == 0) {
			RelEstimPrerec* bullshit = dynamic_cast<RelEstimPrerec*>((*it).get());
			if (bullshit->get_cost(o, h) > 0) {
				needs.push_back((*it)->get_type());
			}
		}
		else if ((*it)->get_general_type().compare("time") == 0) {
			TimePrerec* bullshit = dynamic_cast<TimePrerec*>((*it).get());
			if (bullshit->get_cost() > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type().compare("memory_number") == 0) {
			MemoryNumPrerec* bullshit = dynamic_cast<MemoryNumPrerec*>((*it).get());
			if (bullshit->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type().compare("memory") == 0) {
			MemPrerec* bullshit = dynamic_cast<MemPrerec*>((*it).get());
			if (bullshit->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type().compare("state") == 0) {
			StatePrerec* bullshit = dynamic_cast<StatePrerec*>((*it).get());
			if (bullshit->get_cost() > 0)needs.push_back((*it)->get_type());
		}
	}
	/*
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
	multipliers->setAggression(a);
	multipliers->setKindness(k);
	multipliers->setHonor(h);
	multipliers->setPride(p);
	multipliers->setRecklessness(r);
	multipliers->setExtroversion(e);
	multipliers->setGreed(g);
};

void Action::set_str_mult(int a, int k, int h, int p, int r, int e, int g) {
	str_mult->setAggression(a);
	str_mult->setKindness(k);
	str_mult->setHonor(h);
	str_mult->setPride(p);
	str_mult->setRecklessness(r);
	str_mult->setExtroversion(e);
	str_mult->setGreed(g);
};

void Action::set_aff_mult(int a, int k, int h, int p, int r, int e, int g) {
	aff_mult->setAggression(a);
	aff_mult->setKindness(k);
	aff_mult->setHonor(h);
	aff_mult->setPride(p);
	aff_mult->setRecklessness(r);
	aff_mult->setExtroversion(e);
	aff_mult->setGreed(g);
};

void Action::set_noto_mult(int a, int k, int h, int p, int r, int e, int g) {
	noto_mult->setAggression(a);
	noto_mult->setKindness(k);
	noto_mult->setHonor(h);
	noto_mult->setPride(p);
	noto_mult->setRecklessness(r);
	noto_mult->setExtroversion(e);
	noto_mult->setGreed(g);
};

bool Action::operator==(const Action a) const
{
	if (a.name == name && a.receiver == receiver && a.doer == doer) {
		return true;
	}
	return false;
}