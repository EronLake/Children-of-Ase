#pragma once
#include "stdafx.h"
#include "Player.h"
#include "common.h"

class CheckClass
{
public:
	static Hero* isHero(WorldObj* test);
	static SplSoldier* isSplSoldier(WorldObj* test);
	static Soldier* isSoldier(WorldObj* test);
	static NPC* isNPC(WorldObj* test);
	static LivingObj* isLiving(WorldObj* test);
	static Player* isPlayer(WorldObj* test);
};

