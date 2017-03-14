#pragma once
#include "Player.h"
#include "Attack.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"

class CombatController
{
public:
	CombatController(ChildrenOfOsi* coo);
	~CombatController();
	void addSoldier(Soldier* s) { soldiers.push_back(s); };
	void update();
	void clearSoldiers() { soldiers.clear();};
	void fight(Soldier* sold1, int state);
	void follow(Soldier* follower,Soldier* follow, int state);
	void addtoTargets(Soldier* sold2) { enemyVec.push_back(sold2); };
private:
	vector<Soldier*> soldiers;
	vector<Soldier*> enemyVec;
	ChildrenOfOsi* gameplay_functions;
};

