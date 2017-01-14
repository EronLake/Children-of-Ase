#pragma once
#include "LivingObj.h"
#include "Factions.h"

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(float x, float y, bool col);
	~NPC();
	void setFaction(int f);
	int getFaction();
private:
	int faction;
};

