#pragma once
#include "Soldier.h"
class SplSoldier :
	public Soldier
{
public:
	SplSoldier();
	SplSoldier(float x, float y, bool col);
	~SplSoldier();
	int getAse();
	void setAse(int a);
protected:
	int ase;
	int attacks[3];
};

