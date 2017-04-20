#include "stdafx.h"
#include "Fight.h"

vector<Fight*> Fight::fights_world;

Fight::Fight()
{
	over = false;
	fights_world.push_back(this);
}

Fight::Fight(Party* a, Party* b)
{
	over = false;
	defenders.push_back({a});
	defenders.push_back({b});
	a->set_fight(this);
	b->set_fight(this);
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
	p->set_fight(this);
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
	p->set_fight(this);
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
	p->set_fight(this);
}

void Fight::update_fight() {
	bool ally_erased;
	bool party_erased;
	for (auto it = attackers.begin(); it != attackers.end();) {
		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0){
					downed.push_back((*itor));
				}
				itor = (*it).erase(itor);
				party_erased=true;
			}
			if (!party_erased)++itor;
		}
		if ((*it).size() == 0) {
			it = attackers.erase(it);
			ally_erased = true;
		}
		if (!ally_erased)++it;
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0) {
					downed.push_back((*itor));
				}
				itor = (*it).erase(itor);
				party_erased = true;
			}
			if (!party_erased)++itor;
		}
		if ((*it).size() == 0) {
			it = attackers.erase(it);
			ally_erased = true;
		}
		if (!ally_erased)++it;
	}
	over = check_for_winner();
}

bool Fight::check_for_winner() {
	if (attackers.size() <= 1 && defenders.size() <= 1) {
		unordered_map<Alliance*,int> alliances;
		for (auto it = attackers.begin(); it != attackers.end(); ++it) {
			for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
				if ((*itor)->getMembers().size() > 0) {
					alliances[(*itor)->getLeader()->getVillage()->get_alliance()]=1;
				}
			}
		}
		for (auto it = defenders.begin(); it != defenders.end(); ++it) {
			for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
				if ((*itor)->getMembers().size() > 0) {
					alliances[(*itor)->getLeader()->getVillage()->get_alliance()] = 1;
				}
			}
		}
		return (alliances.size()<=1);
	}
	else {
		return false;
	}
}

void Fight::update_all_fights() {
	for (auto it = fights_world.begin(); it != fights_world.end();) {
		if (!(*it)->is_over())(*it)->update_fight();
	}
}

void Fight::bring_out_your_dead() {
	for (auto it = Party::grave->getMembers().begin(); it != Party::grave->getMembers().end();) {

	}
}