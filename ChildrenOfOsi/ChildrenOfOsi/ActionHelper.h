#pragma once
#include "common.h"
#include "Action.h"
#include "Memory.h"
#include "AIController.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"
#include "Party.h"
#include "Village.h"
#include "DialogueController.h"

class ActionHelper
{

public:
	ActionHelper();
	~ActionHelper();

	//does these need to be static as well?
	static AIController* ai;
	static ChildrenOfOsi* gameplay_func;

	//Create memory
	static void create_memory(Action*, Hero* hero);

	static void battle_sim(Action* train_with, Party* p);
	static void attack_helper(Soldier* attacker, Soldier* defender);
	static void if_kill(Hero* Doer, Hero* Receiver);

	static int retrieve_time(Action* action);
	static void set_timer(Action* action, int wait_time);
	
	static bool conversation(Action* action);
	//Check alliance acceptance 
	//Go to location
	
	//Update memory
	//Collect hero location Timer
	//Battle simulation(timer)

	static bool hero_respond(Action* action);

};

