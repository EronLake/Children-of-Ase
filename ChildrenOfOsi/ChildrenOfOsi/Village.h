#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "Party.h"

class Alliance;

class Village
{
public:
	Village();
	~Village();
	void setStatus(std::string s) { status = s; };
	std::string getStatus() { return status; };
	Village* conquerer;
	vector<Village*> conquered;
	Hero* leader;
	void addToParties(Party* p) { parties.push_back(p); };
	void addToEnemyParties(Party* p) { enemyParties.push_back(p); };
	void removeFromParties(Party* p);
	vector<Party*> getParties() { return parties; };
	bool isEnemyParty(Party* p);
	void clearEnemyParties() { enemyParties.clear(); };
	static vector<Village*> villagesWorld;
	void set_alliance(Alliance* a) { alliance = a; };
	Alliance* get_alliance() { return alliance; };
	vector<NPC*> get_members() { return members; };
	void add_member(NPC* n) { members.push_back(n); n->setVillage(this); };
	void remove_member(NPC* n);


private:
	Alliance* alliance;
	vector<NPC*> members;
	std::string status;
	std::vector<Party*> parties;
	std::vector<Party*> enemyParties;
};

