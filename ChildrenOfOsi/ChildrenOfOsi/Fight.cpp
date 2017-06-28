#include "stdafx.h"
#include "Fight.h"

vector<Fight*> Fight::fights_world;

Fight::Fight()
{
	over = false;
	fights_world.push_back(this);
	sides = 0;
	num_of_fighters=0;
	player_win=true;
}

Fight::Fight(Party* a, Party* b, int tp)
{
	num_of_fighters=0;
	type = tp;
	over = false;
	if (a->get_perm() || (type>0)) {
		defenders.push_back({ a });
	}
	else {
		attackers.push_back({ a });
	}
	if (b->get_perm() || (type>0)) {
		defenders.push_back({ b });
	}
	else {
		attackers.push_back({ b });
	}
	a->set_fight(this);
	b->set_fight(this);
	if (type>0) {
		a->set_killable(false);
		b->set_killable(false);
	}
	else if (!War::at_war(a->get_village(), b->get_village())){
		new War(a->get_village(), b->get_village());
	}
	if (type == 0 || type == 3) {
		a->set_in_combat(true);
		b->set_in_combat(true);
	}
	else {
		a->set_in_duel();
		b->set_in_duel();
	}
	a->addToCurrentEnemies(b);
	b->addToCurrentEnemies(a);
	if (b->getMembers().size() > 0) {
		loc = b->getLeader()->getLoc();
		a->setMode(Party::MODE_DEFEND);
		b->setMode(Party::MODE_DEFEND);
		update_radius();
	}
	sides = 2;
	player_win = true;
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
	num_of_fighters = total_fighters;
	return ((50 * total_fighters) + 750);
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

void Fight::add_party(Party* a, Party* p, bool atk) {
	if (!War::at_war(a->get_village(), p->get_village())) {
		new War(a->get_village(), p->get_village());
	}
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = downed.begin(); it != downed.end(); ++it) {
		if ((*it) == p)return;
	}
	over = false;
	p->set_defend(loc);
	p->setMode(Party::MODE_DEFEND);
	bool added = false;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		if ((*it).size() != 0) {
			if ((*it)[0]->getMembers().size()>0) {
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
	if (type>0)p->set_killable(false);
	if (type == 0 || type == 3) {
		p->set_in_combat(true);
	}
	else {
		p->set_in_duel();
	}
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::add_to_attackers(Party* a, Party* p) {
	if (!War::at_war(a->get_village(), p->get_village())) {
		new War(a->get_village(), p->get_village());
	}
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = downed.begin(); it != downed.end(); ++it) {
		if ((*it) == p)return;
	}
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
	if (type>0)p->set_killable(false);
	if (type == 0 || type == 3) {
		p->set_in_combat(true);
	}
	else {
		p->set_in_duel();
	}
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::add_to_defenders(Party* a, Party* p) {
	if (!War::at_war(a->get_village(), p->get_village())) {
		new War(a->get_village(), p->get_village());
	}
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			if ((*itor) == p)return;
		}
	}
	for (auto it = downed.begin(); it != downed.end(); ++it) {
		if ((*it) == p)return;
	}
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
	if (type>0)p->set_killable(false);
	if (type == 0 || type == 3) {
		p->set_in_combat(true);
	}
	else {
		p->set_in_duel();
	}
	p->setMode(Party::MODE_DEFEND);
	update_radius();
	find_targets();
}

void Fight::update_fight() {
	bool ally_erased;
	bool party_erased;

	Player* player = dynamic_cast<Player*>(Containers::hero_table["Shango"]);
	for (auto it = attackers.begin(); it != attackers.end();) {
		if ((*it)[0]->get_village()== NULL) {
			std::cout << defenders.size();
		}

		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0){
					downed.push_back((*itor));
				}
				if (player->getParty() == (*itor)) {
					if (player->getParty()->get_fight() == this) {
						player_win = false;
					}
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

		if ((*it)[0]->get_village()== NULL) {
			std::cout << defenders.size();
		}

		ally_erased = false;
		for (auto itor = (*it).begin(); itor != (*it).end();) {
			party_erased = false;
			if ((*itor)->getMembers().size() == (*itor)->get_down_members().size()) {
				if ((*itor)->get_down_members().size() > 0) {
					downed.push_back((*itor));
				}
				if (player->getParty() == (*itor)) {
					player_win = false;
				}
				itor = (*it).erase(itor);
				update_radius();
				party_erased = true;
			} else if ((*itor)->getLeader()->getType() == WorldObj::TYPE_PLAYER) {
				if (Party::dist_location_to_location((*itor)->getLeader()->getLoc(), loc) > (rad * 3)) {
					(*itor)->setMode(Party::MODE_FLEE);
					player_win = false;
					itor = (*it).erase(itor);
					update_radius();
					party_erased = true;
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
		if (player->getParty()->get_fight() == this && (player->cur_action!=nullptr && player->cur_action != NULL)) {
			PlayerActExecFunctions::execute_end(player_win);
		}
	}
}

bool Fight::check_for_winner() {
	if (type > 0) {
		if ((attackers.size() + defenders.size()) <= 1) {
			return true;
		}
		else return false;
	}
	else if ((attackers.size() + defenders.size()) <= 1) {
		return true;
	}
	unordered_map<Alliance*, int> alliances;
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		if ((*it).size()>0)alliances[(*it)[0]->get_village()->get_alliance()]=1;
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		if ((*it).size()>0)alliances[(*it)[0]->get_village()->get_alliance()]=1;
	}
	vector<Alliance*> enemy;
	for (auto itor = alliances.begin(); itor != alliances.end(); ++itor) {
		enemy = (*itor).first->get_enemy_alliances();
		for (auto itor2 = enemy.begin(); itor2 != enemy.end(); ++itor2) {
			if (alliances.find((*itor2))!=alliances.end()) {
				return false;
			}
		}
	}
	return true;
}

void Fight::update_all_fights() {
	for (auto it = fights_world.begin(); it != fights_world.end();) {
		if (*it == nullptr || *it == NULL)
		{
			it=fights_world.erase(it);
		}
		else {
			if (!(*it)->is_over())(*it)->update_fight();
			++it;
		}
	}
}

void Fight::bring_out_your_dead() {
	vector<Soldier*> zombies = Party::grave->getMembers();
	for (auto it = zombies.begin(); it != zombies.end(); ++it) {
		if (!(*it)->sprite.getLock()) {
			Party::grave->removeSoldier((*it),false);
			if ((*it)->getType() < WorldObj::TYPE_HERO) {
				(*it)->getVillage()->barracks->addToParty((*it), false);
				(*it)->setHealth((*it)->get_max_health());
				(*it)->setInCombat(false);
				(*it)->setLoc((*it)->getVillage()->get_village_location());
			}
		}
	}
}

void Fight::end_combat() {
	for (auto it = attackers.begin(); it != attackers.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_in_combat(false);
			(*itor)->setMode(Party::MODE_ATTACK);
			if ((type>0))(*itor)->capacitate_all(type);
			if ((type>0))(*itor)->set_killable(true);
		}
	}
	for (auto it = defenders.begin(); it != defenders.end(); ++it) {
		for (auto itor = (*it).begin(); itor != (*it).end(); ++itor) {
			(*itor)->set_in_combat(false);
			(*itor)->setMode(Party::MODE_ATTACK);
			if ((type>0))(*itor)->capacitate_all(type);
			if ((type>0))(*itor)->set_killable(true);
		}
	}
	for (auto itor = downed.begin(); itor != downed.end(); ++itor) {
		(*itor)->set_in_combat(false);
		(*itor)->setMode(Party::MODE_ATTACK);
		if ((type>0))(*itor)->capacitate_all(type);
		if ((type>0))(*itor)->set_killable(true);
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
		if (Party::dist_location_to_location(p->getLeader()->getLoc(), loc) > (rad)) {
			p->setMode(Party::MODE_FLEE);
			player_win = false;
		}
	}
	else if (p->getLeader()->getType() == WorldObj::TYPE_HERO) {
		vector<Party*> enemies = p->getCurrentEnemies();
		int total_enemies = 0;
		int total_sold = num_of_fighters;
		for (auto it = enemies.begin(); it != enemies.end(); ++it) {
			total_enemies += (*it)->getMembers().size();
		}
		int tmp = sides - 1;
		if (tmp < 1)tmp = 1;
		total_sold = total_sold - total_enemies;
		total_enemies = total_enemies / tmp;
		if (total_enemies > (total_sold * 3) && ((p->getLeader()->getHealth()*4)<=p->getLeader()->get_max_health())) {
			p->setMode(Party::MODE_FLEE);
		}
	}
	else {
		vector<Party*> enemies = p->getCurrentEnemies();
		int total_enemies = 0;
		int total_sold = num_of_fighters;
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

void Fight::remove_from_downed(Party* p) {
	for (auto it = downed.begin(); it != downed.end();++it) {
		if ((*it) == p) {
			downed.erase(it);
			return;
		}
	}
}