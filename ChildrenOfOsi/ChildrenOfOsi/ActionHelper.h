#pragma once
#include "common.h"
#include "Action.h"
#include "Memory.h"

#include "AIController.h"

class ActionHelper
{

public:
	ActionHelper();
	~ActionHelper();

	static AIController* ai;

	static void create_memory(Action* );

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

