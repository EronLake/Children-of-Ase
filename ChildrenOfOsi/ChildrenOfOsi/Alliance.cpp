#include "stdafx.h"
#include "Alliance.h"


Alliance::Alliance()
{
}


Alliance::~Alliance()
{
	//force the destructor if there are no factions in the alliance(as result of merging to another alliance perhaps)
}

void Alliance::addToAlliance(Factions * p_faction)
{
	allies.push_back(p_faction);
}

void Alliance::removeFromAlliance(Factions * p_factionToRemove)
{
	allies.erase(std::remove(allies.begin(), allies.end(), p_factionToRemove), allies.end());
}
