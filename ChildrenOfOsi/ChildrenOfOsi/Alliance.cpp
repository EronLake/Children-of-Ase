#include "stdafx.h"
#include "Alliance.h"
std::vector<Alliance*> Alliance::Alliances;

Alliance::Alliance()
{
	Alliance::Alliances.push_back(this);
}

Alliance::Alliance(Village* v)
{
	allies.push_back(v);
	Alliance::Alliances.push_back(this);
	v->set_alliance(this);
}

Alliance::~Alliance()
{
	//force the destructor if there are no factions in the alliance(as result of merging to another alliance perhaps)
}

void Alliance::add_village_to_alliance(Village * p_faction)
{
	allies.push_back(p_faction);
	std::vector<Village*> tmp = War::getWars(p_faction);
	for (int j = 0; j < tmp.size(); j++) {
		enemies.push_back(tmp[j]);
	}
	p_faction->set_alliance(this);
}

void Alliance::add_alliance_to_alliance(Alliance* p_alliance)
{
	vector<Village*> tmp = p_alliance->get_alligned_villages();
	for (auto p_faction = tmp.begin(); p_faction != tmp.end(); ++p_faction) {
		this->add_village_to_alliance(*p_faction);
	}
	Alliance::remove_alliance(p_alliance);
}

void Alliance::remove_village_from_alliance(Village * p_factionToRemove)
{
	allies.erase(std::remove(allies.begin(), allies.end(), p_factionToRemove), allies.end());
	for (auto it = allies.begin(); it != allies.end(); ++it) {
		if (p_factionToRemove == *it) {
			allies.erase(it);
		}
		else {
			vector<Party*> party = (*it)->getParties();
			for (auto it2 = party.begin(); it2 != party.end();++it2) {
				vector<Soldier*> soldiers = (*it2)->getMembers();
				Party* p = new Party();
				for (auto it3 = soldiers.begin(); it3 != soldiers.end(); ++it3) {
					if ((*it3)->getVillage() == p_factionToRemove) {
						p->addToParty(*it3,true);
						(*it2)->removeSoldier(*it3);
					}
				}
				if (p->getMembers().size() != 0) {
					p->set_home((*it)->get_village_location());
					p->setMode(Party::MODE_FLEE);
					p_factionToRemove->addToParties(p);
				}
				if ((*it2)->getMembers().size() == 0) {
					(*it)->remove_party(*it2);
				}
			}
		}
	}
	new Alliance(p_factionToRemove);
	if (allies.size() == 0) {
		Alliance::remove_alliance(this);
	}
	update_enemies();
}

void Alliance::remove_alliance(Alliance * p_alliance)
{
	Alliance::Alliances.erase(std::remove(Alliance::Alliances.begin(), Alliance::Alliances.end(), p_alliance), Alliance::Alliances.end());
	update_enemies();
}

void Alliance::update_enemies() {
	for (auto itor = Alliance::Alliances.begin(); itor != Alliance::Alliances.end(); ++itor) {
		(*itor)->enemies.clear();
		for (int i = 0; i < (*itor)->allies.size(); i++) {
			(*itor)->allies[i]->clearEnemyParties();
			std::vector<Village*> tmp = War::getWars((*itor)->allies[i]);
			for (int j = 0; j < tmp.size(); j++) {
				std::vector<Village*> tmp2 = tmp[j]->get_alliance()->get_alligned_villages();
				for (int k = 0; k < tmp2.size();k++) {
					(*itor)->enemies.push_back(tmp2[k]);
				}
			}
		}
		for (int i = 0; i < (*itor)->allies.size(); i++) {
			for (int j = 0; j < (*itor)->enemies.size(); j++) {
				vector<Party*> eparts = (*itor)->enemies[j]->getParties();
				for (int z = 0; z < eparts.size(); z++) {
					(*itor)->allies[i]->addToEnemyParties(eparts[z]);
				}
			}
		}
	}
}

vector<NPC*> Alliance::get_alliance_members() {
	vector<NPC*> tmp;
	for (auto it = allies.begin(); it != allies.end(); ++it) {
		vector<NPC*> tmp2= (*it)->get_members();
		for (auto itor= tmp2.begin(); itor!=tmp2.end();++itor){
			tmp.push_back(*itor);
		}
	}
	return tmp;
}

bool Alliance::is_alliance_member(NPC* n) {
	vector<NPC*> tmp=this->get_alliance_members();
	for (auto it = tmp.begin(); it != tmp.end(); ++it) {
		if (n == *it)return true;
	}
	return false;
}