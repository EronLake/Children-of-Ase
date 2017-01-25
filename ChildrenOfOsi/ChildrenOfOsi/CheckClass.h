#pragma once
#include "stdafx.h"
#include "Hero.h"
#include "common.h"

class CheckClass
{
public:
	static bool isHero(WorldObj* test);
	static bool isSplSoldier(WorldObj* test);
	static bool isSoldier(WorldObj* test);
	static bool isNPC(WorldObj* test);
	static bool isLiving(WorldObj* test);
};

