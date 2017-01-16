#pragma once
#include "NPC.h"
class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(float x, float y, bool col);
	~Soldier();
	int getAtk();
	void setAtk(int a);
	void goAtk(LivingObj *target);
	void setInCombat(bool c);
	bool getInCombat();
private:
	int atk;
	bool inCombat;
};
