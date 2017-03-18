#pragma once
#include "common.h"
#include "Party.h"

class PartyManager
{
public:
	PartyManager();
	~PartyManager();

	void updateAggroStatus();
	void checkForEnemy();


private:
	vector<Party*> parties;

};

