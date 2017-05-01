#include "stdafx.h"
#include "War.h"
std::vector<War*> War::wars;

War::War()
{
	wars.push_back(this);
}

War::~War()
{
}

void War::setWarParties(Village * p_alliance1, Village * p_alliance2)
{
	//checks if already in a war
	bool if_already_waring = false;
	for (int i = 0; i < wars.size(); i++)
	{
		if (p_alliance1 == wars[i]->getWarParties().first || p_alliance1 == wars[i]->getWarParties().second &&
			p_alliance2 == wars[i]->getWarParties().first || p_alliance2 == wars[i]->getWarParties().second)
		{
			if_already_waring = true;
		}
	}
	if (!if_already_waring) {
		warParties.first = p_alliance1;
		warParties.second = p_alliance2;
	}
}

std::pair<Village*, Village*> War::getWarParties()
{
	return warParties;
}

void War::endWar(Village* one, Village* two) {
	for (auto i = wars.begin(); i !=wars.end();++i) {
		if ((*i)->getWarParties().first==one) {
			if ((*i)->getWarParties().second == two) {
				delete *i;
				i = wars.erase(i);
				i--;
			}
		} else if ((*i)->getWarParties().first==two) {
			if ((*i)->getWarParties().second == one) {
				delete *i;
				i = wars.erase(i);
				i--;
			}
		}
	}
}

std::vector<Village*> War::getWars(Village* vil) {
	std::vector<Village*> tmp;
	for (auto i = wars.begin(); i != wars.end(); ++i) {
		if ((*i)->getWarParties().first == vil) {
			tmp.push_back((*i)->warParties.second);
		} else if ((*i)->getWarParties().second == vil) {
			tmp.push_back((*i)->warParties.first);
		}
	}
	return tmp;
}