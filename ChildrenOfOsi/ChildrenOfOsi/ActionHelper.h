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

	//Check alliance acceptance 
	//Go to location
	//Create memory
	//Update memory
	//Collect hero location Timer
	//Battle simulation(timer)

	static bool hero_respond(Action* act);

	static void execute_train(Action* train);
	static void execute_train_with(Action* train_with);

};

