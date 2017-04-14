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

	action->time_stamp = frame_count;//int time = get world time
	std::string category = "incomplete";
	string where = "not yet defined";
	int when = -1;

	//string category;         //ACTIONS: fail, success, incomplete     FACTS: fact type (i.e. name, origin, etc)
	//string content;          //ACTIONS: action name                   FACTS: actual data (i.e. "Yemoja", "Oasis", etc)
	//string where;            //ACTIONS: where the event occured                              
	//int why;                 //ACTIONS: do-er's motivation (0=affinity, 1=strength, 2=notoriety, -1=idk)
	//int when;                //ACTIONS: when the event occured (incomplete: when it started, complete: when it completed)
	//string reason;           //ACTIONS: reason for failure or success
	//Memory(int t, int frames, vector<NPC*> p, string cat="",string cont="",string where="",int why=-1, int when=-1);
	gameplay_func->add_memory(key, hero->name, type, action->time_stamp, people, category,action->getName() + std::to_string(action->time_stamp), where, action->getWhy(), when);
	hero->mem_counter++;

	if (hero->name = OYA)
	{
		hero->memories.push_back(Containers::oya_memory_table[key]);
		bool the_same_ptr = hero->memories[0] = Containers::oya_memory_table[key];
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

void ActionHelper::battle_sim(Action* battle, Party* p)
{
		//may we have offensive team attack first? Slightly randomized
		Party* Attackers = battle->getDoer()->cur_party;
		Party* Defenders = p;

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
	damage += attacker->melee->getDmg();
	damage += rand() % (damage * 2) - damage;
	//take average of all attacks
	damage = damage / attacker->attackTypes.size()+1;
	//take off damage from the average of all their attacks AKA larger attack smaller
	defender->addHealth(-damage);

	//check if the attacked part has died
	if (defender->getHealth() <= 0)
	{
		//kill the soldier/incapacitate the Hero if they run out of health
		defender->defeat();
		if (defender->getType()<5) {
			defender->setLoc(defender->getVillage()->get_village_location());
			defender->getVillage()->barracks->addToParty(defender, false);
		}
	}
}

void ActionHelper::if_kill(Hero* Doer, Hero* Receiver)
{
	if (Doer->rel[Receiver->name]->getAffinity() < 10) {
		Receiver->kill();

		//need to add the memory to memories
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

bool ActionHelper::conversation(Action* action) {
	Relationship before = *action->getDoer()->rel[action->getReceiver()->name];

	//conversation
	dialogue_point point = { "Fake", "Response_" +action->getName()};
	DialogueController::dialogue.gen_dialog(point,action->getReceiver(),1,1);

	int success_level = 0;
	for (auto it = action->succ_postconds.begin(); it != action->succ_postconds.end(); ++it) {
		if ((*it)->get_general_type() == Postcondition::REL) {
			RelPost* con = dynamic_cast<RelPost*>((*it).get());
			switch (con->get_rel_type()) {
			case Postcondition::AFF:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getAffinity()-before.getAffinity();
				break;
			case Postcondition::NOT:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getNotoriety() - before.getNotoriety();
				break;
			case Postcondition::STR:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getStrength() - before.getStrength();
				break;
			case Postcondition::BAFF:
				success_level += before.getAffinity()-action->getDoer()->rel[action->getReceiver()->name]->getAffinity();
				break;
			case Postcondition::BNOT:
				success_level += before.getNotoriety() - action->getDoer()->rel[action->getReceiver()->name]->getNotoriety();
				break;
			case Postcondition::BSTR:
				success_level += before.getStrength() - action->getDoer()->rel[action->getReceiver()->name]->getStrength();
				break;
			}
		} else if ((*it)->get_general_type() == Postcondition::REL_EST) {
			RelEstimPost* con = dynamic_cast<RelEstimPost*>((*it).get());
			switch (con->get_rel_type()) {
			case Postcondition::AFF:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getAffEstimate() - before.getAffEstimate();
				break;
			case Postcondition::NOT:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getNotorEstimate() - before.getNotorEstimate();
				break;
			case Postcondition::STR:
				success_level += action->getDoer()->rel[action->getReceiver()->name]->getStrEstimate() - before.getStrEstimate();
				break;
			case Postcondition::BAFF:
				success_level += before.getAffEstimate() - action->getDoer()->rel[action->getReceiver()->name]->getAffEstimate();
				break;
			case Postcondition::BNOT:
				success_level += before.getNotorEstimate() - action->getDoer()->rel[action->getReceiver()->name]->getNotorEstimate();
				break;
			case Postcondition::BSTR:
				success_level += before.getStrEstimate() - action->getDoer()->rel[action->getReceiver()->name]->getStrEstimate();
				break;
			}
		}
	}
	return (success_level>0);
}

ChildrenOfOsi* ActionHelper::gameplay_func;