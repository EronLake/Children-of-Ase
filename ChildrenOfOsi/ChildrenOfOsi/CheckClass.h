#pragma once
#include "stdafx.h"
#include "Player.h"
#include "common.h"

class CheckClass
{
public:
	static Hero* isHero(WorldObj* test);
	static bool isSplSoldier(WorldObj* test);
	static bool isSoldier(WorldObj* test);
	static bool isNPC(WorldObj* test);
	static bool isLiving(WorldObj* test);
	static bool isPlayer(WorldObj* test);
};

