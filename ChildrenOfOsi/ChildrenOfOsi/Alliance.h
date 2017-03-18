#pragma once

#include "common.h"
#include "Village.h"
#include "War.h"
#include "Party.h"

class Alliance
{
private:
	std::vector<Village*> allies;
	std::vector<Village*> enemies;
	static std::vector<Alliance*>Alliances;

public:
	Alliance();
	Alliance(Village* v);
	~Alliance();
	void addToAlliance(Village* p_factionToAdd);
	vector<Village*> getAllignedVillages(){ return allies; };
	void removeFromAlliance(Village* p_factionToRemove);
	static void updateEnemies();
};

