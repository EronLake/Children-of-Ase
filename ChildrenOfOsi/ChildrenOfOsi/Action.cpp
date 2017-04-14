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
	checkpoint = 0; //used for action execution

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

void Action::apply_postconditions(bool ifsucc)
{
	if (ifsucc == true) 
	{
		for (int i = 0; i < succ_postconds.size(); i++)
		{
			if (succ_postconds[i]->get_general_type() ==Postcondition::REL || succ_postconds[i]->get_general_type() == Postcondition::REL_EST)
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
			if (fail_postconds[i]->get_general_type() == Postcondition::REL || fail_postconds[i]->get_general_type() == Postcondition::REL_EST)
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
		if ((*it)->get_general_type()==Preconditions::REL) {
			RelPrecon* bullshit= dynamic_cast<RelPrecon*>((*it).get());
			int temp = bullshit->get_cost(o, h);
			if (bullshit->get_cost(o, h) > 0) {
				std::string temp2 = (*it)->get_type();
				needs.push_back(temp2);
			}
		}
		else if ((*it)->get_general_type() == Preconditions::REL_EST) {
			RelEstimPrerec* bullshit = dynamic_cast<RelEstimPrerec*>((*it).get());
			if (bullshit->get_cost(o, h) > 0) {
				needs.push_back((*it)->get_type());
			}
		}
		else if ((*it)->get_general_type() == Preconditions::TIME) {
			TimePrerec* bullshit = dynamic_cast<TimePrerec*>((*it).get());
			if (bullshit->get_cost() > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
			MemoryNumPrerec* bullshit = dynamic_cast<MemoryNumPrerec*>((*it).get());
			if (bullshit->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::MEM) {
			MemPrerec* bullshit = dynamic_cast<MemPrerec*>((*it).get());
			if (bullshit->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::STATE) {
			StatePrerec* bullshit = dynamic_cast<StatePrerec*>((*it).get());
			if (bullshit->get_cost() > 0)needs.push_back((*it)->get_type());
		}
	}
	if (!optional_fufilled_check(o,h)) {
		for (auto itor = op_preconds.begin(); itor != op_preconds.end(); ++itor) {
			for (auto it = (*itor).begin(); it != (*itor).end(); ++it) {
				if ((*it)->get_general_type() == Preconditions::REL) {
					RelPrecon* bullshit = dynamic_cast<RelPrecon*>((*it).get());
					if (bullshit->get_cost(o, h) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::REL_EST) {
					RelEstimPrerec* bullshit = dynamic_cast<RelEstimPrerec*>((*it).get());
					if (bullshit->get_cost(o, h) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::TIME) {
					TimePrerec* bullshit = dynamic_cast<TimePrerec*>((*it).get());
					if (bullshit->get_cost() > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
					MemoryNumPrerec* bullshit = dynamic_cast<MemoryNumPrerec*>((*it).get());
					if (bullshit->get_cost(o->memories) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::MEM) {
					MemPrerec* bullshit = dynamic_cast<MemPrerec*>((*it).get());
					if (bullshit->get_cost(o->memories) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::STATE) {
					StatePrerec* bullshit = dynamic_cast<StatePrerec*>((*it).get());
					if (bullshit->get_cost() > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
			}
		}
	}
	//std::////cout << "HERE 2.5" << endl;*/
	return needs;
}

int Action::exeAction() {
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

vector<std::string> Action::add_no_repeats(vector<std::string> v, string s) {
	for (auto it = v.begin(); it != v.end(); ++it) {
		if ((*it).compare(s)==0)return v;
	}
	v.push_back(s);
	return v;
}

bool Action::optional_fufilled_check(Hero* o, Hero* h) {
	for (auto itor = op_preconds.begin(); itor != op_preconds.end(); ++itor) {
		bool one_fufilled = true;
		for (auto it = (*itor).begin(); it != (*itor).end(); ++it) {
			if ((*it)->get_general_type() == Preconditions::REL) {
				RelPrecon* bullshit = dynamic_cast<RelPrecon*>((*it).get());
				if (bullshit->get_cost(o, h) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::REL_EST) {
				RelEstimPrerec* bullshit = dynamic_cast<RelEstimPrerec*>((*it).get());
				if (bullshit->get_cost(o, h) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::TIME) {
				TimePrerec* bullshit = dynamic_cast<TimePrerec*>((*it).get());
				if (bullshit->get_cost() > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
				MemoryNumPrerec* bullshit = dynamic_cast<MemoryNumPrerec*>((*it).get());
				if (bullshit->get_cost(o->memories) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::MEM) {
				MemPrerec* bullshit = dynamic_cast<MemPrerec*>((*it).get());
				if (bullshit->get_cost(o->memories) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::STATE) {
				StatePrerec* bullshit = dynamic_cast<StatePrerec*>((*it).get());
				if (bullshit->get_cost() > 0) {
					one_fufilled = false;
				}
			}
		}
		if (one_fufilled)return true;
	}
	return false;
}