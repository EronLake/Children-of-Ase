#include "stdafx.h"
#include "ActionHelper.h"

AIController* ActionHelper::ai = nullptr;

ActionHelper::ActionHelper()
{
	LOG("ActionHelper Object Constructed");
}


ActionHelper::~ActionHelper()
{
	LOG("ActionHelper Object Destroyed");
}

void ActionHelper::create_memory(Action* action) {
	int type = 0;           
	vector<NPC*> people;
	people.push_back(action->getDoer());/*needs to be changed to did*/
	people.push_back(action->getReceiver());
	people.push_back(action->getOwner());

	string category;         //ACTIONS: fail, success, incomplete                            FACTS: fact type (i.e. name, origin, etc)
	string content;          //ACTIONS: action name                                          FACTS: actual data (i.e. "Yemoja", "Oasis", etc)
	string where;            //ACTIONS: where the event occured                              
	int why;                 //ACTIONS: do-er's motivation (0=affinity, 1=strength, 2=notoriety, -1=idk)
	int when;                //ACTIONS: when the event occured (incomplete: when it started, complete: when it completed)
	string reason;           //ACTIONS: reason for failure or success

	//int time;/ 


	//Memory(int t, int frames, vector<NPC*> p, string cat="",string cont="",string where="",int why=-1, int when=-1);

}

//For actions that require the receiver to decide
//whether or not to stop their current_action and participate
//
//Compares the given action's value to the receiver's current_action_value
//to determine whether the receiver will accept the interaction
bool ActionHelper::hero_respond(Action* act) {
	bool interact = true;

	int doer = act->getDoer()->name;
	int responder = act->getReceiver()->name;

	Planner* hero_planner = ai->hero_planners[responder];

	int value = hero_planner->value_of(act);

	if (value < 0) {  //This action's cost outweights its benefit, no thanks
		interact = false;
	}
	//The value of my current action is at least twice as big as this action's value. No thanks
	else if (value < (hero_planner->get_current_action_value() - value)) 
	{
		interact = true;
	}

	return interact;
}

void ActionHelper::execute_train(Action* train) {

}

void ActionHelper::execute_train_with(Action* train_with) {

}
void ActionHelper::execute_form_alliance(Action* form_alliance) {

}