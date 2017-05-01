#include "stdafx.h"
#include "Fight.h"

vector<Fight*> Fight::fights_world;

Fight::Fight()
{
	over = false;
	fights_world.push_back(this);
	sides = 0;
}

Fight::Fight(Party* a, Party* b, bool duel)
{
	over = false;
	if (a->get_perm() || duel) {
		defenders.push_back({ a });
	}
	else {
		attackers.push_back({ a });
	}
	if (b->get_perm() || duel) {
		defenders.push_back({ b });
	}
	else {
		attackers.push_back({ b });
	}
	a->set_fight(this);
	b->set_fight(this);
	a->set_in_combat(true);
	b->set_in_combat(true);
	a->addToCurrentEnemies(b);
	b->addToCurrentEnemies(a);
	if (b->getMembers().size() > 0) {
		loc = b->getLeader()->getLoc();
		a->setMode(Party::MODE_DEFEND);
		b->setMode(Party::MODE_DEFEND);
		update_radius();
	}
	sides = 2;
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
	rad = get_radius();
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_defend(loc);
			(*itor)->set_def_rad(rad);
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_defend(loc);
			(*itor)->set_def_rad(rad);
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		(*itor)->set_defend(loc);
		(*itor)->set_def_rad(rad);
	}
}

void Fight::add_party(Party* p, bool atk) {
	over = false;
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
		if (atk && !p->get_perm()) {
			attackers.push_back({ p });
		}
		else {
			defenders.push_back({ p });
		}
	}
	p->set_fight(this);
	p->set_in_combat(true);
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::add_to_attackers(Party* p) {
	over = false;
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
	p->set_in_combat(true);
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::add_to_defenders(Party* p) {
	over = false;
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
	p->set_in_combat(true);
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::update_fight() {
	bool ally_erased;
	bool party_erased;
	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);
	for (auto it = attackers.begin(); it != attackers.end();) {
		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0){
					downed.push_back((*itor));
				}
				if (player->getParty() == (*itor)) {
					if (player->getParty()->get_fight() == this);
					PlayerActExecFunctions::execute_end(false);
				}
				itor = (*it).erase(itor);
				update_radius();
				party_erased=true;
			}else {
				check_should_flee((*itor));
				if ((*itor)->getMode() == Party::MODE_FLEE) {
					itor = (*it).erase(itor);
					update_radius();
					party_erased = true;
				}
			}
			if (!party_erased)++itor;
		}
		if ((*it).size() == 0) {
			it = attackers.erase(it);
			ally_erased = true;
			find_targets();
		}
		if (!ally_erased)++it;
	}
	for (auto it = defenders.begin(); it != defenders.end();) {
		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0) {
					downed.push_back((*itor));
				}
				if (player->getParty() == (*itor)) {
					if (player->getParty()->get_fight() == this);
					PlayerActExecFunctions::execute_end(false);
				}
				itor = (*it).erase(itor);
				update_radius();
				party_erased = true;
			} else if ((*itor)->getLeader()->getType() == WorldObj::TYPE_PLAYER) {
				if (Party::dist_location_to_location((*itor)->getLeader()->getLoc(), loc) > (rad * 3)) {
					(*itor)->setMode(Party::MODE_FLEE);
				}
			}
			if (!party_erased)++itor;
		}
		if ((*it).size() == 0) {
			it = defenders.erase(it);
			ally_erased = true;

			find_targets();
		}
		if (!ally_erased)++it;
	}
	update_radius();
	over = check_for_winner();
	if (over) {
		if (player->getParty()->get_fight() == this) {
			PlayerActExecFunctions::execute_end(true);
		}
	}
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
		if (alliances.size() <= 1) {
			//end_combat();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Fight::update_all_fights() {
	for (auto it = fights_world.begin(); it != fights_world.end();++it) {
		if (!(*it)->is_over())(*it)->update_fight();
	}
}

void Fight::bring_out_your_dead() {
	vector<Soldier*> zombies = Party::grave->getMembers();
	for (auto it = zombies.begin(); it != zombies.end(); ++it) {
		if (!(*it)->sprite.getLock()) {
			(*it)->setLoc((*it)->getVillage()->get_village_location());
			Party::grave->removeSoldier((*it),false);
			(*it)->getVillage()->barracks->addToParty((*it),false);
			(*it)->setHealth((*it)->get_max_health());
			(*it)->setInCombat(false);
		}
	}
}

void Fight::end_combat() {
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_in_combat(false);
			(*itor)->setMode(Party::MODE_ATTACK);
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_in_combat(false);
			(*itor)->setMode(Party::MODE_ATTACK);
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		(*itor)->set_in_combat(false);
		(*itor)->setMode(Party::MODE_ATTACK);
	}
	over = true;
}

//combines attack/defend/downed vectors into a map by alliance
void Fight::find_targets() {
	unordered_map<Alliance*, vector<Party*>> alliances;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor)->getMembers().size() > 0) {
				alliances[(*itor)->getLeader()->getVillage()->get_alliance()].push_back((*itor));
			}
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor)->getMembers().size() > 0) {
				alliances[(*itor)->getLeader()->getVillage()->get_alliance()].push_back((*itor));
			}
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		if ((*itor)->getMembers().size() > 0) {
			alliances[(*itor)->getLeader()->getVillage()->get_alliance()].push_back((*itor));
		}
	}
	sides = alliances.size();
	help_find_targets(alliances);
}

//uses map to find enemies
void Fight::help_find_targets(unordered_map<Alliance*, vector<Party*>> alliances){
	vector<Alliance*> enmys;
	vector<Party*> enmys_party;
	vector<Party*> allies;
	for (auto it = alliances.begin(); it != alliances.end(); ++it) {
		allies = ((*it).second);
		enmys = ((*it).first)->get_enemy_alliances();
		for (int i = 0; i < enmys.size(); i++) {
			enmys_party = alliances[enmys[i]];
			for (auto itor = allies.begin(); itor != allies.end(); ++itor) {
				(*itor)->clear_current_enemies();
				for (int j = 0; j < enmys_party.size();j++) {
					(*itor)->addToCurrentEnemies(enmys_party[j]);
				}
			}
		}
	}
}

void Fight::check_should_flee(Party* p) {
	if (p->getLeader()->getType() == WorldObj::TYPE_PLAYER) {
		if (Party::dist_location_to_location(p->getLeader()->getLoc(), loc) > (rad * 3)) {
			p->setMode(Party::MODE_FLEE);
		}
	}
	else if (p->getLeader()->getType() == WorldObj::TYPE_HERO) {
		vector<Party*> enemies = p->getCurrentEnemies();
		int total_enemies = 0;
		int total_sold = rad / 100;
		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			total_enemies += (*it)->getMembers().size();
		}
		int tmp = sides - 1;
		if (tmp < 1)tmp = 1;
		total_sold = total_sold - total_enemies;
		total_enemies = total_enemies / tmp;
		if (total_enemies > (total_sold * 3)) {
			p->setMode(Party::MODE_FLEE);
		}
	}
	else {
		vector<Party*> enemies = p->getCurrentEnemies();
		int total_enemies = 0;
		int total_sold = rad / 100;
		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			total_enemies += (*it)->getMembers().size();
		}
		int tmp= sides-1;
		if (tmp < 1)tmp = 1;
		total_sold = total_sold-total_enemies;
		total_enemies = total_enemies / tmp;

		if (total_enemies > (total_sold*2)) {
			p->setMode(Party::MODE_FLEE);
		}
	}
}