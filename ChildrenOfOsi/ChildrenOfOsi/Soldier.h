#pragma once
#include "NPC.h"
#include "stdafx.h"
#include "Attack.h"

class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(float x, float y, bool col);
	Soldier(Vector2f p_topLeft, float p_width, float p_height);
	~Soldier();
	void setInCombat(bool c) { inCombat = c; };
	bool getInCombat() { return inCombat; };
	Attack melee;
	vector<Attack*>atkType;
	vector<Attack*>available;
	unordered_map<Attack*,int> cdMap;
	Attack* newAttack(int i);
	void meleeAttack();
	void setCD(int c) { cdTotal = c; };
	int getCD() { return cdTotal; };
	void updateCD() { if (cdFrame >= cdTotal) { cdFrame++; } else cool = true; };
	int framesCD() { return cdFrame; };
	void setCool(bool c) { cool = c; };
	bool getCool() { return cool; };
private:
	bool inCombat;
	int cdTotal;
	int cdFrame;
	bool cool;
};

