#pragma once
#include "common.h"
#include "Player.h"
#include "Alliance.h"

class Party
{
public:
	Party();
	~Party();
	void addToParty(Soldier* s, bool lead);
	void removeFromParty(Soldier* s);
	void setLeader(Soldier* s);
	Soldier* getLeader() { return leader; };
	void setAlliance(Alliance* a) { faction = a; };
	Alliance* getAlliance() { return faction; };
	void setMode(int m);
	int getMode() { return mode; };

	vector<Soldier*> getParty() { vector<Soldier*> full_group = members; full_group.push_back(leader); return full_group; };
	
private:
	vector<Soldier*> members;
	Soldier* leader;
	Alliance* faction; // LOL
	int mode;   // 0: Idle
				// 1: Attack
				// 2: Defend
				// 3: Patrol
				// 4: Flee
};

