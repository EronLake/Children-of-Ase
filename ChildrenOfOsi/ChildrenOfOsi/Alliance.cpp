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
	std::vector<Village*> tmp = War::getWars(p_faction);
	for (int j = 0; j < tmp.size(); j++) {
		enemies.push_back(tmp[j]);
	}
}

Alliance* Alliance::removeFromAlliance(Village * p_factionToRemove)
{
	allies.erase(std::remove(allies.begin(), allies.end(), p_factionToRemove), allies.end());
	Alliance* newAll = new Alliance(p_factionToRemove);
	newAll->updateEnemies();
	updateEnemies();
	return newAll;
}

void Alliance::updateEnemies() {
	enemies.clear();
	for (int i = 0; i < allies.size(); i++) {
		std::vector<Village*> tmp = War::getWars(allies[i]);
		for (int j = 0; j < tmp.size(); j++) {
			enemies.push_back(tmp[j]);
		}
	}
}
