#pragma once
#include "common.h"
#include "Hero.h"
#include "Player.h"
#include "Action.h"
#include "Containers.h"
#include "ActionHelper.h"
#include "Fight.h"

class PlayerActExecFunctions
{
public:
	PlayerActExecFunctions();
	~PlayerActExecFunctions();

	static void execute_start(std::string act_name, Hero* receiver);
	static void execute_end(bool if_succ);
	static void check_quest();
};

