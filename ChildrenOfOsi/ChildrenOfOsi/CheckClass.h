#pragma once
#include "stdafx.h"
#include "Player.h"
#include "common.h"

class CheckClass
{
public:
	static bool isHero(WorldObj* test, Hero* hero = nullptr);
	static bool isSplSoldier(WorldObj* test, SplSoldier* spl = nullptr);
	static bool isSoldier(WorldObj* test, Soldier* soldier = nullptr);
	static bool isNPC(WorldObj* test, NPC* npc = nullptr);
	static bool isLiving(WorldObj* test, LivingObj* living = nullptr);
	static bool isPlayer(WorldObj* test, Player* player = nullptr);
};

