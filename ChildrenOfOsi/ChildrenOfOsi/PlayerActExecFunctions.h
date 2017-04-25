#pragma once
#include "common.h"
#include "Hero.h"
#include "Player.h"
#include "Action.h"
#include "Containers.h"
#include "ActionHelper.h"

class PlayerActExecFunctions
{
public:
	PlayerActExecFunctions();
	~PlayerActExecFunctions();

	static void execute_start(std::string act_name, Player* player/*this is always the player*/, Hero* receiver);
	static void execute_end();
};

