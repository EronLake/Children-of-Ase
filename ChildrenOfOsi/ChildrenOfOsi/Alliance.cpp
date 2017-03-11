#include "stdafx.h"
#include "Alliance.h"


Alliance::Alliance()
{
}

Alliance::Alliance(Village* v)
{
	allies.push_back(v);
}

Alliance::~Alliance()
{
	//force the destructor if there are no factions in the alliance(as result of merging to another alliance perhaps)
}

void Alliance::addToAlliance(Village * p_faction)
{
	allies.push_back(p_faction);
}

Alliance* Alliance::removeFromAlliance(Village * p_factionToRemove)
{
	allies.erase(std::remove(allies.begin(), allies.end(), p_factionToRemove), allies.end());
	return new Alliance(p_factionToRemove);
}
