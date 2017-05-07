#include "stdafx.h"
#include "Alliance.h"
#include "War.h"
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
	update_enemies();
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
	update_enemies();
}

void Alliance::add_alliance_to_alliance(Alliance* p_alliance)
{
	vector<Village*> tmp = p_alliance->get_alligned_villages();
	for (auto p_faction = tmp.begin(); p_faction != tmp.end(); ++p_faction) {
		bool already_in_alliance = false;
		for (auto ally_village = this->allies.begin(); ally_village != this->allies.end(); ++ally_village){
			if (*ally_village == *p_faction) { already_in_alliance = true; }
		}
		
		if (!already_in_alliance) { this->add_village_to_alliance(*p_faction); }
	}
	Alliance::remove_alliance(p_alliance);
	update_enemies();
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
						(*it2)->removeSoldier(*it3, false);
						p->addToParty(*it3,true);
					}
				}
				if (p->getMembers().size() != 0) {
					p->set_home((p_factionToRemove)->get_village_location());
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
		(*itor)->enemy_alliances.clear();
		for (int i = 0; i < (*itor)->allies.size(); i++) {
			std::vector<Village*> tmp = War::getWars((*itor)->allies[i]);
			for (int j = 0; j < tmp.size(); j++) {
				bool not_there = true;
				std::vector<Alliance*> vnm = (*itor)->enemy_alliances;
				for (auto it = vnm.begin(); it != vnm.end(); ++it) {
					if ((*it) == tmp[j]->get_alliance())not_there = false;
				}
				if (not_there)(*itor)->enemy_alliances.push_back(tmp[j]->get_alliance());
				std::vector<Village*> tmp2 = tmp[j]->get_alliance()->get_alligned_villages();
				for (int k = 0; k < tmp2.size();k++) {
					bool not_there2 = true;
					std::vector<Village*> venm = (*itor)->enemies;
					for (auto it = venm.begin(); it != venm.end(); ++it) {
						if ((*it) == tmp2[k])not_there2 = false;
					}
					if (not_there2)(*itor)->enemies.push_back(tmp2[k]);
				}
			}
		}
	}
}

/*vector<Alliance*> Alliance::get_enemy_alliances() {
	vector<Alliance*> ret;
	unordered_map<Alliance*, int> mkshft;
	vector<Village*> enmys;
	for (auto it = allies.begin(); it != allies.end();++it) {
		enmys = War::getWars((*it));
		for (auto itor = enmys.begin(); itor != enmys.end(); ++itor) {
			mkshft[(*itor)->get_alliance()] = 1;
		}
	}
	for (auto itr = mkshft.begin(); itr != mkshft.end(); ++itr) {
		ret.push_back((*itr).first);
	}
	return ret;
}*/

vector<Hero*> Alliance::get_leaders() {
	vector<Hero*> leads;
	for (auto it = allies.begin(); it != allies.end(); ++it) {
		Hero* ret = (*it)->leader;
		if (ret->getType() == WorldObj::TYPE_PLAYER) return { ret };
		leads.push_back(ret);
	}
	return leads;
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
	return(n->getVillage()->get_alliance() == this);
}