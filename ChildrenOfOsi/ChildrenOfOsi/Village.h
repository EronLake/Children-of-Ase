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
	Alliance* alliance;
	vector<NPC*> members;
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
private:
	std::string status;
	std::vector<Party*> parties;
	std::vector<Party*> enemyParties;
};

