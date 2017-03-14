#pragma once
#include "common.h"
#include "Action.h"
#include "Memory.h"
#include "AIController.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"
#include "Party.h"
#include "ActionHelper.h"

typedef void(*execute_ptr)(Action* cur_action);

class ActionExecFunctions
{
public:
	ActionExecFunctions();
	~ActionExecFunctions();

	static void execute_train(Action* train);
	static void execute_train_with(Action* train_with);
	static void execute_fight(Action* fight);
	static void execute_form_alliance(Action* form_alliance);

	

	static std::unordered_map<std::string, execute_ptr> ActionExecMap;
};

