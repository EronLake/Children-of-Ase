#pragma once

#include "common.h"
#include "Village.h"

class Alliance
{
private:
	std::vector<Village*> allies;

public:
	Alliance();
	Alliance(Village* v);
	~Alliance();
	void addToAlliance(Village* p_factionToAdd);
	Alliance* removeFromAlliance(Village* p_factionToRemove);
};

