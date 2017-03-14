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

void ActionHelper::battle_sim(Action* battle)
{
		//may we have offensive team attack first? Slightly randomized
		Party* Attackers = battle->getDoer()->cur_party;
		Party* Defenders = battle->getReceiver()->cur_party;

		vector<Soldier*> larger;
		vector<Soldier*> smaller;
		//Check which party is l larger
		
		//this pairs every solider with a counterpart in the other party
		//with the larger team ganging up on the smaller one
		if (Attackers->getMembers().size() >= Defenders->getMembers().size())
		{ 
			larger = Attackers->getMembers();
			smaller = Defenders->getMembers();

			// all attackers attack first
			for (int i = 0; i < larger.size(); i++)
			{
				attack_helper(Attackers->getMembers()[i], Defenders->getMembers()[i%smaller.size()]);
			}
			//all defenders attack second
			for (int i = 0; i < smaller.size(); i++)
			{
				attack_helper(Defenders->getMembers()[i], Attackers->getMembers()[i]);
			}
		}
		else
		{
			smaller = Attackers->getMembers();
			larger = Defenders->getMembers();

			// all attackers attack first
			for (int i = 0; i < smaller.size(); i++)
			{
			attack_helper(Attackers->getMembers()[i], Defenders->getMembers()[i]);
			}
			//all defenders attack second
			for (int i = 0; i < larger.size(); i++)
			{
			attack_helper(Defenders->getMembers()[i], Attackers->getMembers()[i%smaller.size()]);
			}
		}
		

}

void ActionHelper::attack_helper(Soldier* attacker, Soldier* defender)
{
	//total damage of all attacks
	int damage = 0;
	for (int a = 0; a < attacker->attackTypes.size(); a++)
	{
		damage += attacker->attackTypes[a]->getDmg();
	}
	//take average of all attacks
	damage = damage / attacker->attackTypes.size();
	//take off damage from the average of all their attacks AKA larger attack smaller
	defender->addHealth(-damage);

	//check if the attacked part has died
	if (defender->getHealth() <= 0)
	{
		//kill the soldier/incapacitate the Hero if they run out of health
		defender->defeat();
	}
}


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
				int temp = 0;
				for (auto& iter : form_alliance->preconds) {
					
					temp += iter.second->get_cost();
				}
				if (temp != 0) {
					//success
					for (auto& i : form_alliance->postconds) {

					i.second->apply_utility();
					}
				}
				else {
					//failed
				}
			}
			else {
				//update memory failed
			}

		}
		
	}
}

void ActionHelper::fight(Action* fight) 
{
	/*	/Create Memory
		/Locate hero (maybe start by going to heroes village)
		/Travel to village
		/check if there/reset desination and find target
		/Engage in battle (talk first?)
		If win - update with win post conditions 
		Else - update with lost post conditions
		Update memory all participants with memory
		Prompt for kill?
	*/

	switch (fight->checkpoint) {
	case 0: //Pick village location(location of fight target), create memory, increment checkpoint
		fight->getDoer()->destination = { 1000,1000 }; //need to somehow retrieve location of target village
		create_memory(fight, fight->getDoer());
		fight->checkpoint++;
		break;
	case 1: //If destination is reached, check if hero is there start a timer and move if not, fight otherwise
		if (fight->getDoer()->destination == Vector2f(0, 0))//needs to be changed to use party location right 
		{
			//if the target hero is in the village then begin the battle
			if (fight->getDoer()->getLoc() == fight->getReceiver()->getLoc()) // need to change this so it checks if the party is close by
			{
				fight->checkpoint+= 2;
			}
			set_timer(fight, 3600);  //Wait 1 minute (60 frames times 60 seconds) trying to find out the hero's location
			fight->checkpoint++;
		}
		break;
	case 2: //If timer is complete, set village as destination to the location of the target hero 
		if (retrieve_time(fight) == 0) 
		{
			fight->getDoer()->destination = fight->getReceiver()->getLoc(); //go to the target hero's location
			fight->checkpoint++;
		}
		break;
	case 3: //If both niether party is empty then contiue the fight 
		//(may need to change this to account for hero death)
		if (fight->getDoer()->getParty()->getMembers().size() == 0 || fight->getReceiver()->getParty()->getMembers().size() == 0) 
		{
			fight->checkpoint++;
		} 
		//do a single round of battle every 10 sec
		if (retrieve_time(fight) == 0)
		{
			battle_sim(fight);
			set_timer(fight, 600);
		}

		//NEED TO SOMEHOW ACCOUNT FOR IF A PLAYER GETS CLOSE
		
		break;
	case 4: //If win update apply win-post else apply loss-post and update memory
		//check if the target's party is empty(may need to change this to account for hero death)
		if (fight->getReceiver()->getParty()->getMembers().size() == 0) {
			//Apply succ-post-conditions
														 											 
		}
		else
		{
			//Apply fail-post-conditions
		}

		//Call update_memory function
		//Mark action as executed?
		//create prompt for kill action
		break;

	}

}

ChildrenOfOsi* ActionHelper::gameplay_func;