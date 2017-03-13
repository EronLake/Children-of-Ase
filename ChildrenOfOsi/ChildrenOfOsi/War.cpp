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
	warParties.first = p_alliance1;
	warParties.second = p_alliance2;
}

std::pair<Village*, Village*> War::getWarParties()
{
	return warParties;
}

void War::endWar(Village* one, Village* two) {
	for (auto i = wars.begin(); i !=wars.end();++i) {
		if ((*i)->getWarParties().first==one) {
			if ((*i)->getWarParties().second == two) {
				wars.erase(i);
			}
		} else if ((*i)->getWarParties().first==two) {
			if ((*i)->getWarParties().second == one) {
				wars.erase(i);
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