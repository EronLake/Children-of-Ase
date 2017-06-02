#include "stdafx.h"
#include "War.h"
std::vector<War*> War::wars;

War::War(Village* one, Village* two)
{
	this->setWarParties(one,two);
	wars.push_back(this);
	Alliance::update_enemies();
}

War::~War()
{
}

void War::setWarParties(Village * p_alliance1, Village * p_alliance2)
{
	warParties.first = p_alliance1;
	warParties.second = p_alliance2;
	if (p_alliance1->get_alliance() == p_alliance2->get_alliance()) {
			p_alliance2->get_alliance()->remove_village_from_alliance(p_alliance1);
	}
	Alliance::update_enemies();
}

std::pair<Village*, Village*> War::getWarParties()
{
	return warParties;
}

void War::endWar(Village* one, Village* two) {
	for (auto i = wars.begin(); i !=wars.end();++i) {
		if (((*i)->getWarParties().first == one || (*i)->getWarParties().first == two) &&
			((*i)->getWarParties().second == one || (*i)->getWarParties().second == two)) {
			delete *i;
			i = wars.erase(i);
			Alliance::update_enemies();
			return;
		}
	}
}

void War::end_wars() {
	for (int i = 0; i < wars.size(); i++) {
		endWar(wars[i]->warParties.first, wars[i]->warParties.second);
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

bool War::at_war(Village* one, Village* two) {
	for (int i = 0; i < wars.size(); i++)
	{
		if (one == wars[i]->getWarParties().first || one == wars[i]->getWarParties().second &&
			two == wars[i]->getWarParties().first || two == wars[i]->getWarParties().second)
		{
			return true;
		}
	}
	return false;
}