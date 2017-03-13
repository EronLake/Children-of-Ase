#pragma once
#include "common.h"
#include "Action.h"
#include "Memory.h"
#include "AIController.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"

class ActionHelper
{

public:
	ActionHelper();
	~ActionHelper();

	//does these need to be static as well?
	static AIController* ai;
	static ChildrenOfOsi* gameplay_func;


	static void create_memory(Action*, Hero* hero);

	static int retrieve_time(Action* action);
	static void set_timer(Action* action, int wait_time);

	//Check alliance acceptance 
	//Go to location
	//Create memory
	//Update memory
	//Collect hero location Timer
	//Battle simulation(timer)

	static bool hero_respond(Action* action);

	static void execute_train(Action* train);
	static void execute_train_with(Action* train_with);
	static void execute_form_alliance(Action* form_alliance);

};

