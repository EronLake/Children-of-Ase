#pragma once
#include "NPC.h"
#include "stdafx.h"
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
	void setWidth(float w) { width = w; };
	void setHeight(float h) { height = h; }
	float getWidth() { return width; }
	float getHeight() { return height; }
private:
	int atk;
	bool inCombat;
	float width;
	float height;
};

