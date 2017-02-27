#include "stdafx.h"
#include "CheckClass.h"
Hero* CheckClass::isHero(WorldObj* test) 
{ 
	Hero* hero;
	hero = dynamic_cast<Hero*>(test);
	return hero;
}

SplSoldier* CheckClass::isSplSoldier(WorldObj* test)
{
	SplSoldier* spl;
	spl = dynamic_cast<SplSoldier*>(test);
	return spl;
}

Soldier* CheckClass::isSoldier(WorldObj* test)
{
	Soldier* soldier;
	soldier = dynamic_cast<Soldier*>(test);
	return soldier;
}

NPC* CheckClass::isNPC(WorldObj* test)
{
	NPC* npc;
	npc = dynamic_cast<NPC*>(test);
	return npc;
}

LivingObj* CheckClass::isLiving(WorldObj* test)
{
	LivingObj* living;
	living = dynamic_cast<LivingObj*>(test);
	return living;
}

Player* CheckClass::isPlayer(WorldObj* test)
{
	Player* player;
	player = dynamic_cast<Player*>(test);
	return player;
}