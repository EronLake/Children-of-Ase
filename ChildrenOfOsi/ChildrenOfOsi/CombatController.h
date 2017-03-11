#pragma once
#include "Player.h"
#include "Attack.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"

class CombatController
{
public:
	CombatController();
	~CombatController();
	void addSoldier(Soldier* s) { soldiers.push_back(s); };
	void update();
	void clearSoldiers() { soldiers.clear();};
private:
	vector<Soldier*> soldiers;
};

