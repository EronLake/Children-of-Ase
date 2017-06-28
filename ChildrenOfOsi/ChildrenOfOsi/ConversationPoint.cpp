#include "stdafx.h"
#include "ConversationPoint.h"


ConversationPoint::ConversationPoint()
{
}


ConversationPoint::~ConversationPoint()
{
	delete multipliers;
	delete rel_multipliers;
}

void ConversationPoint::setMultipliers(int a, int k, int h, int p, int r, int e, int g) {
	multipliers = new Personality();
	multipliers->setAggression(a);
	multipliers->setKindness(k);
	multipliers->setHonor(h);
	multipliers->setPride(p);
	multipliers->setRecklessness(r);
	multipliers->setExtroversion(e);
	multipliers->setGreed(g);
};

std::string ConversationPoint::get_icon() {
	return icon;
}

std::string ConversationPoint::get_temp() {
	return temp;
}

std::string ConversationPoint::get_name() {
	return my_name;
}

std::string ConversationPoint::get_topic() {
	return topic;
}

std::string ConversationPoint::get_is_selectable() {
	return is_selectable;
}

Action* ConversationPoint::get_action() {
	return act;
}

void ConversationPoint::set_icon(std::string val) {
	icon = val;
}

void ConversationPoint::set_temp(std::string val) {
	temp = val;
}

void ConversationPoint::set_name(std::string val) {
	my_name = val;
}

void ConversationPoint::set_topic(std::string val) {
	topic = val;
}

void ConversationPoint::set_is_selectable(std::string val) {
	is_selectable = val;
}

void ConversationPoint::set_action(Action* action) {
	act = action;
}

/*
applies the post conditions (this affect the hero receiver and world)
the the actual change in relationships are handled by the conditions'
apply utility function
*/
void ConversationPoint::apply_postconditions(bool ifsucc, Hero* doer,Hero* receiver)
{
	//creates pointer to post
	vector<std::shared_ptr<Postcondition>>* doer_postconds;
	vector<std::shared_ptr<Postcondition>>* receiver_postconds;

	//this decides based off the ifsucc flag is the succ or fail post conditions should be applied
	if (ifsucc == true)
	{
		doer_postconds = &doer_succ_postconds;
		receiver_postconds = &receiver_succ_postconds;
	}
	else {
		doer_postconds = &doer_fail_postconds;
		receiver_postconds = &receiver_fail_postconds;
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



