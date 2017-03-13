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

void ActionHelper::create_memory(Action* action, Hero* hero)
{
	std::string key = std::to_string(hero->mem_counter);
	int type = 0;           
	std::vector<NPC*> people;
	people.push_back(action->getDoer());/*needs to be changed to did*/
	people.push_back(action->getReceiver());
	people.push_back(action->getOwner());

	int time = 0;//int time = get world time
	std::string category = "incomplete";
	string where = NULL;
	int when = -1;
	

	//string category;         //ACTIONS: fail, success, incomplete     FACTS: fact type (i.e. name, origin, etc)
	//string content;          //ACTIONS: action name                   FACTS: actual data (i.e. "Yemoja", "Oasis", etc)
	//string where;            //ACTIONS: where the event occured                              
	//int why;                 //ACTIONS: do-er's motivation (0=affinity, 1=strength, 2=notoriety, -1=idk)
	//int when;                //ACTIONS: when the event occured (incomplete: when it started, complete: when it completed)
	//string reason;           //ACTIONS: reason for failure or success

	//Memory(int t, int frames, vector<NPC*> p, string cat="",string cont="",string where="",int why=-1, int when=-1);
	gameplay_func->add_memory(key, hero->name, type, time, people, category,action->getName(), where, action->getWhy(), when);
	hero->mem_counter++;

	if (hero->name = OYA)
	{
		hero->memories.push_back(Containers::oya_memory_table[key]);
	}
	else if (hero->name = YEMOJA)
	{
		hero->memories.push_back(Containers::yemoja_memory_table[key]);
	}
	else if (hero->name = OSHOSI)
	{
		hero->memories.push_back(Containers::oshosi_memory_table[key]);
	}
	else if (hero->name = OGUN)
	{
		hero->memories.push_back(Containers::ogun_memory_table[key]);
	}
	else if (hero->name = SHANGO)
	{
		hero->memories.push_back(Containers::shango_memory_table[key]);
	}
}
/*
static void battle_sim(Action* battle) 
{{
		//may we have offensive team attack first? Slightly randomized
		Party* Attackers = battle->getDoer()->cur_party;
		Party* Defenders = battle->getReceiver()->cur_party;

		vector<Soldier*> larger;
		vector<Soldier*> smaller;
		//Check which party is l larger
		if (Attackers->getParty().size() >= Defenders->getParty().size())
		{
			larger = Attackers->getParty();
			smaller = Attackers->getParty();
		}
		else
		{
			smaller = Attackers->getParty();
			larger = Attackers->getParty();
		}

			for(int i = 0; i < larger.size(); i++)
			{
			larger[i] party_small[i%party_small.size()]
			Party_large[i] attack(reduce health with the worth of one attack) with
			party_small[i%party_small.size()]

			if (party_small[i%party_small.size()] 	heath == 0) remove from party
			(kill / retreat)

				party_small[i%party_small.size()] attack(reduce health with the worth of
					one attack) with Party_large[i]

				if (Party_large[i] heath == 0) remove from party
				(kill / retreat)
		}

}
*/

//Decrement the action's timer and return its new value. 
//Whenever a Hero is a "waiting", this function would be called
//every frame and determines when the waiting is done
int ActionHelper::retrieve_time(Action* action) {
	if (action->current_timer > 0) {
		action->current_timer--;
	}
	return action->current_timer;
}

//Used whenever a Hero needs to wait for a set amount of time during
//the execution of an action
//Called once at the start of the "waiting", intiates the Action's timer with
//the given wait_time value. 
void ActionHelper::set_timer(Action* action, int wait_time) {
	action->current_timer = wait_time;
}

//For actions that require the receiver to decide
//whether or not to stop their current_action and participate
//
//Compares the given action's value to the receiver's current_action_value
//to determine whether the receiver will accept the interaction
bool ActionHelper::hero_respond(Action* action) {
	bool interact = true;

	int doer = action->getDoer()->name;
	int responder = action->getReceiver()->name;

	Planner* hero_planner = ai->hero_planners[responder];

	int value = hero_planner->value_of(action);

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
	switch (train->checkpoint) {
	case 0: //Pick training location, create memory, increment checkpoint
		train->getDoer()->destination = { 1000,1000 }; //should select from set of pre-defined, stored in Hero, or village?
		create_memory(train, train->getDoer());
		train->checkpoint++;
		break;
	case 1: //If destination is reached, start a timer and move to next checkpoint
		if (train->getDoer()->destination == Vector2f(0, 0)) {
			set_timer(train, 3600);  //Wait 1 minute (60 frames times 60 seconds)
			train->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination, apply postconds, update memory
		if (retrieve_time(train) == 0) {
			train->getDoer()->destination = { 500,500 }; //Also predefined, maybe as "home_location" in hero
			//Apply post-conditions
			//Call update_memory function
			//Mark action as executed?
		}
		break;

	}
}

void ActionHelper::execute_train_with(Action* train_with) {

}
void ActionHelper::execute_form_alliance(Action* form_alliance) {
	Hero* doer = form_alliance->getDoer();
	Hero* responder = form_alliance->getReceiver();
	switch (form_alliance->checkpoint) {
	case 0:
		create_memory(form_alliance, doer);
		
		form_alliance->getDoer()->destination = { 1000,1000 };
		form_alliance->checkpoint++;
		break;

	case 1:
		if (form_alliance->getDoer()->destination == Vector2f(0, 0)) {
			Planner* hero_planner = ai->hero_planners[responder->name];
			if (form_alliance->getName() == ((*hero_planner->get_end_state_map())[responder->name]).getName()){
				if (!form_alliance->exeAction()) {
					//update memory failed
				}
				else {
					//update memory success
					//add receiver to doer's alliance
				}
			}
			else {
				//update memory failed
			}

		}
		
	}
}

ChildrenOfOsi* ActionHelper::gameplay_func;