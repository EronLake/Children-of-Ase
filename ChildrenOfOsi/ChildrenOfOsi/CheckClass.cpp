#include "stdafx.h"
#include "CheckClass.h"
Hero* CheckClass::isHero(WorldObj* test) 
{
	Hero* d = dynamic_cast<Hero*>(test);
	return d;
}

bool CheckClass::isSplSoldier(WorldObj* test)
{
	if (SplSoldier* d = dynamic_cast<SplSoldier*>(test)) return true;
	else return false;
}

bool CheckClass::isSoldier(WorldObj* test)
{
	if (Soldier* d = dynamic_cast<Soldier*>(test)) return true;
	else return false;
}

bool CheckClass::isNPC(WorldObj* test)
{
	if (NPC* d = dynamic_cast<NPC*>(test)) return true;
	else return false;
}

bool CheckClass::isLiving(WorldObj* test)
{
	if (LivingObj* d = dynamic_cast<LivingObj*>(test)) return true;
	else return false;
}

bool CheckClass::isPlayer(WorldObj* test)
{
	if (Player* d = dynamic_cast<Player*>(test)) return true;
	else return false;
}