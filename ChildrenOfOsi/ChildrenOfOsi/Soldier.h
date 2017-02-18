#pragma once
#include "NPC.h"
#include "stdafx.h"
class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(float x, float y, bool col);
	Soldier(Vector2f p_topLeft, float p_width, float p_height);
	~Soldier();
	int getAtk();
	void setAtk(int a);
	void goAtk(LivingObj *target);
	void setInCombat(bool c);
	bool getInCombat();

private:
	int atk;
	bool inCombat;
	float width;
	float height;
};

