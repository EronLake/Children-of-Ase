#pragma once
#include "NPC.h"
#include "stdafx.h"
#include "Projectile.h"
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
	Projectile melee;
	vector<Projectile*> atkTypes;
	Projectile* newAttack(int i);
	void meleeAttack();
private:
	bool inCombat;
};

