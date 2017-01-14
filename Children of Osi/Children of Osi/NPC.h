#pragma once
#include "LivingObj.h"

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(float x, float y, bool col);
	~NPC();
private:
	int faction;
};

