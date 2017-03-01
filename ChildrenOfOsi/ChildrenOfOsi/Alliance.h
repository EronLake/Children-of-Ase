#pragma once

#include "common.h"
#include "Factions.h"

class Alliance
{
private:
	std::vector<Factions*> allies;

public:
	Alliance();
	~Alliance();
	void addToAlliance(Factions* p_factionToAdd);
	void removeFromAlliance(Factions* p_factionToRemove);
};

