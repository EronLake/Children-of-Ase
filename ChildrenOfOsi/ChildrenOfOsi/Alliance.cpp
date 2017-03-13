#include "stdafx.h"
#include "Alliance.h"
std::vector<Alliance*> Alliance::Alliances;

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

void Alliance::removeFromAlliance(Village * p_factionToRemove)
{
	allies.erase(std::remove(allies.begin(), allies.end(), p_factionToRemove), allies.end());
	Alliance::Alliances.push_back(new Alliance(p_factionToRemove));
	updateEnemies();
}

void Alliance::updateEnemies() {
	for (auto itor = Alliance::Alliances.begin(); itor != Alliance::Alliances.end(); ++itor) {
		(*itor)->enemies.clear();
		for (int i = 0; i < (*itor)->allies.size(); i++) {
			std::vector<Village*> tmp = War::getWars((*itor)->allies[i]);
			for (int j = 0; j < tmp.size(); j++) {
				(*itor)->enemies.push_back(tmp[j]);
			}
		}
	}
}
