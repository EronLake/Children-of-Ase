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
	if (receiver != nullptr)recieverName = receiver->name;
	name = _name;
	exe_name = _exe_name;
	execute_ptr = ActionExecFunctions::ActionExecMap[_exe_name];
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

/*
applies the post conditions (this affect the hero receiver and world)
the the actual change in relationships are handled by the conditions'
apply utility function
*/
void Action::apply_postconditions(bool ifsucc)
{
	//creates pointer to post
	vector<std::shared_ptr<Postcondition>>* doer_postconds;
	vector<std::shared_ptr<Postcondition>>* receiver_postconds;

	//this decides based off the ifsucc flag is the succ or fail post conditions should be applied
	if (ifsucc == true)
	{
		doer_postconds = &doer_succ_postconds;
		receiver_postconds = &receiver_fail_postconds;
	}
	else {
		doer_postconds = &doer_fail_postconds;
		receiver_postconds = &receiver_succ_postconds;
	}

	//applies all post conditions associated with the action to the doer
	for (int i = 0; i < (*doer_postconds).size(); i++)
	{
		if ((*doer_postconds)[i]->get_general_type() == Postcondition::REL || (*doer_postconds)[i]->get_general_type() == Postcondition::REL_EST)
		{
			(*doer_postconds)[i]->apply_utility(doer, receiver, true); //the true value says this is the doer
		}
		else
		{
			(*doer_postconds)[i]->apply_utility();
		}
	}

	//applies all post conditions associated with the action to the reciever
	for (int i = 0; i < (*receiver_postconds).size(); i++)
	{
		if ((*receiver_postconds)[i]->get_general_type() == Postcondition::REL || (*receiver_postconds)[i]->get_general_type() == Postcondition::REL_EST)
		{
			(*receiver_postconds)[i]->apply_utility(doer, receiver, false); //the false value says this is the reciver
		}
		else
		{
			(*receiver_postconds)[i]->apply_utility();
		}
	}

}

vector<std::string> Action::preConditionsNeeded(Hero* o, Hero* h) {
	vector<std::string> needs;
	for (auto it = req_preconds.begin(); it != req_preconds.end(); ++it) {
		if ((*it)->get_general_type() == Preconditions::REL) {

			//if (bullshit->get_cost(o, h) > 0) {
			//	std::string temp2 = (*it)->get_type();
			//needs.push_back(temp2);

			RelPrecon* condition = dynamic_cast<RelPrecon*>((*it).get());
			if (condition->get_cost(o, h) > 0) {
				needs.push_back((*it)->get_type());
			}
		}
		else if ((*it)->get_general_type() == Preconditions::REL_EST) {
			RelEstimPrerec* condition = dynamic_cast<RelEstimPrerec*>((*it).get());
			if (condition->get_cost(o, h) > 0) {
				needs.push_back((*it)->get_type());
			}
		}
		else if ((*it)->get_general_type() == Preconditions::TIME) {
			TimePrerec* condition = dynamic_cast<TimePrerec*>((*it).get());
			if (condition->get_cost() > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
			MemoryNumPrerec* condition = dynamic_cast<MemoryNumPrerec*>((*it).get());
			if (condition->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::MEM) {
			MemPrerec* condition = dynamic_cast<MemPrerec*>((*it).get());
			if (condition->get_cost(o->memories) > 0)needs.push_back((*it)->get_type());
		}
		else if ((*it)->get_general_type() == Preconditions::STATE) {
			StatePrerec* condition = dynamic_cast<StatePrerec*>((*it).get());
			if (condition->get_cost() > 0)needs.push_back((*it)->get_type());
		}
	}
	if (!optional_fufilled_check(o, h)) {
		for (auto itor = op_preconds.begin(); itor != op_preconds.end(); ++itor) {
			for (auto it = (*itor).begin(); it != (*itor).end(); ++it) {
				if ((*it)->get_general_type() == Preconditions::REL) {
					RelPrecon* condition = dynamic_cast<RelPrecon*>((*it).get());
					if (condition->get_cost(o, h) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::REL_EST) {
					RelEstimPrerec* condition = dynamic_cast<RelEstimPrerec*>((*it).get());
					if (condition->get_cost(o, h) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::TIME) {
					TimePrerec* condition = dynamic_cast<TimePrerec*>((*it).get());
					if (condition->get_cost() > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
					MemoryNumPrerec* condition = dynamic_cast<MemoryNumPrerec*>((*it).get());
					if (condition->get_cost(o->memories) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::MEM) {
					MemPrerec* condition = dynamic_cast<MemPrerec*>((*it).get());
					if (condition->get_cost(o->memories) > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
				else if ((*it)->get_general_type() == Preconditions::STATE) {
					StatePrerec* condition = dynamic_cast<StatePrerec*>((*it).get());
					if (condition->get_cost() > 0) {
						needs = add_no_repeats(needs, (*it)->get_type());
					}
				}
			}
		}
	}
	//std:://////cout << "HERE 2.5" << endl;*/
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
		if ((*it).compare(s) == 0)return v;
	}
	v.push_back(s);
	return v;
}

bool Action::optional_fufilled_check(Hero* o, Hero* h) {
	for (auto itor = op_preconds.begin(); itor != op_preconds.end(); ++itor) {
		bool one_fufilled = true;
		for (auto it = (*itor).begin(); it != (*itor).end(); ++it) {
			if ((*it)->get_general_type() == Preconditions::REL) {
				RelPrecon* condition = dynamic_cast<RelPrecon*>((*it).get());
				if (condition->get_cost(o, h) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::REL_EST) {
				RelEstimPrerec* condition = dynamic_cast<RelEstimPrerec*>((*it).get());
				if (condition->get_cost(o, h) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::TIME) {
				TimePrerec* condition = dynamic_cast<TimePrerec*>((*it).get());
				if (condition->get_cost() > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::MEM_NUM) {
				MemoryNumPrerec* condition = dynamic_cast<MemoryNumPrerec*>((*it).get());
				if (condition->get_cost(o->memories) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::MEM) {
				MemPrerec* condition = dynamic_cast<MemPrerec*>((*it).get());
				if (condition->get_cost(o->memories) > 0) {
					one_fufilled = false;
				}
			}
			else if ((*it)->get_general_type() == Preconditions::STATE) {
				StatePrerec* condition = dynamic_cast<StatePrerec*>((*it).get());
				if (condition->get_cost() > 0) {
					one_fufilled = false;
				}
			}
		}
		if (one_fufilled)return true;
	}
	return false;
}