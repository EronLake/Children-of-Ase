#include "stdafx.h"
#include "Fight.h"

vector<Fight*> Fight::fights_world;

Fight::Fight()
{
	fights_world.push_back(this);
}

Fight::Fight(Party* a, Party* b)
{
	fights_world.push_back(this);
}

Fight::~Fight()
{
}

int Fight::get_radius() {
	int total_fighters = 0;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			total_fighters += (*itor)->getMembers().size();
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			total_fighters += (*itor)->getMembers().size();
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		total_fighters += (*itor)->getMembers().size();
	}
	return (100 * total_fighters);
}

void Fight::update_radius() {
	int rad = get_radius();
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_def_rad(rad);
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_def_rad(rad);
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		(*itor)->set_def_rad(rad);
	}
}

void Fight::add_party(Party* p, bool atk) {
	p->set_defend(loc);
	p->setMode(Party::MODE_DEFEND);
	bool added = false;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		if ((*it).size() != 0) {
			Soldier* lead = (*it)[0]->getLeader();
			if (p->getMembers().size() != 0) {
				Soldier* sofp = p->getLeader();
				if (lead->getVillage()->get_alliance() == sofp->getVillage()->get_alliance()) {
					(*it).push_back(p);
					added = true;
				}
			}
		}
	}
	if (!added) {
		for (auto it = defenders.begin(); it != defenders.end(); ++it) {
			if ((*it).size() != 0) {
				Soldier* lead = (*it)[0]->getLeader();
				if (p->getMembers().size() != 0) {
					Soldier* sofp = p->getLeader();
					if (lead->getVillage()->get_alliance() == sofp->getVillage()->get_alliance()) {
						(*it).push_back(p);
						added = true;
					}
				}
			}
		}
	}
	if (!added) {
		if (atk) {
			attackers.push_back({ p });
		}
		else {
			defenders.push_back({ p });
		}
	}
}

void Fight::add_to_attackers(Party* p) {
	bool added = false;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		if ((*it).size() != 0) {
			Soldier* lead = (*it)[0]->getLeader();
			if (p->getMembers().size() != 0){
				Soldier* sofp = p->getLeader();
				if (lead->getVillage()->get_alliance() == sofp->getVillage()->get_alliance()) {
					(*it).push_back(p);
					added = true;
				}
			}
		}
	}
	if (!added)attackers.push_back({p});
}

void Fight::add_to_defenders(Party* p) {
	bool added = false;
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		if ((*it).size() != 0) {
			Soldier* lead = (*it)[0]->getLeader();
			if (p->getMembers().size() != 0) {
				Soldier* sofp = p->getLeader();
				if (lead->getVillage()->get_alliance() == sofp->getVillage()->get_alliance()) {
					(*it).push_back(p);
					added = true;
				}
			}
		}
	}
	if (!added)defenders.push_back({ p });
}

void Fight::update_fight() {

}

void Fight::update_all_fights() {

}

void Fight::bring_out_your_dead() {

}