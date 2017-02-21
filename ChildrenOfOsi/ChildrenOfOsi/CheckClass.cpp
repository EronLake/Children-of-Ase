#include "stdafx.h"
#include "CheckClass.h"
bool CheckClass::isHero(WorldObj* test, Hero* hero) 
{
	if (hero = dynamic_cast<Hero*>(test)) return true;
	else return false;
}

bool CheckClass::isSplSoldier(WorldObj* test, SplSoldier* spl)
{
	if (spl = dynamic_cast<SplSoldier*>(test)) return true;
	else return false;
}

bool CheckClass::isSoldier(WorldObj* test, Soldier* soldier)
{
	if (soldier = dynamic_cast<Soldier*>(test)) return true;
	else return false;
}

bool CheckClass::isNPC(WorldObj* test, NPC* npc)
{
	if (npc = dynamic_cast<NPC*>(test)) return true;
	else return false;
}

bool CheckClass::isLiving(WorldObj* test, LivingObj* living)
{
	if (living = dynamic_cast<LivingObj*>(test)) return true;
	else return false;
}

bool CheckClass::isPlayer(WorldObj* test, Player* player)
{
	if (player = dynamic_cast<Player*>(test)) return true;
	else return false;
}