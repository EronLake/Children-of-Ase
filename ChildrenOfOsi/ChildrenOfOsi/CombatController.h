#pragma once
#include "Player.h"
#include "Attack.h"
#include "ChildrenOfOsi.h"

class CombatController
{
public:
	CombatController();
	~CombatController();
	void addSoldier(Soldier* s) { soldiers.push_back(s); };
	void addAttack(Attack* a) { attacks.push_back(a); };
	void update();
	void clearSoldiers() { soldiers.clear();};
	void removeAttack(Attack* a);
	vector<Attack*> getAttacks() { return attacks; };
private:
	vector<Soldier*> soldiers;
	vector<Attack*> attacks;
};

