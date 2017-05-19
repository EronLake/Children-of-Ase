#pragma once
#include "Attack.h"
#include "ChildrenOfOsi.h"
#include "Containers.h"
#include "Fight.h"

class CombatController
{
public:
	CombatController(ChildrenOfOsi* coo);
	~CombatController();
	void addSoldier(Soldier* s) { soldiers.push_back(s); };
	void clearSoldiers() { soldiers.clear();};
	void fight(Soldier* sold1, int state);
	void follow(Soldier* follower, int state);
	void update_soldier(Soldier* sold1, int state);
	void find_closest_enemy(Soldier* sold1, int state);
	bool find_closest_friend(Soldier* sold1, int state);
	void move_to_target(Soldier* sold1, int state);
	void addtoTargets(Soldier* sold2) { enemyVec.push_back(sold2); };
	static float dist_by_center(Soldier* sold1, Soldier* sold2);
	static float dist_soldier_to_location(Soldier* sold1, Vector2f loc);
	static float dist(Vector2f start, Vector2f end);
	void checkParties();
	void party_leader_update(Soldier* sold1, int state);
	void updateSoliderStatus();
	std::thread threaded_update_soldier(Soldier* s, int n);
	bool shot_ligned_up(Vector2f atkr, Vector2f target);
private:
	vector<Soldier*> soldiers;
	vector<Soldier*> enemyVec;
	ChildrenOfOsi* gameplay_functions;
};

