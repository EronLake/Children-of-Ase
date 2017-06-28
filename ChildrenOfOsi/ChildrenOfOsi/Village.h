#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "Party.h"

class Alliance;

class Village
{
public:
	Village();
	~Village();
	void setStatus(std::string s) { status = s; };
	std::string getStatus() { return status; };
	Hero* leader;
	void addToParties(Party* p) { p->setAlliance(alliance);
	p->set_village(this); p->set_home(location); parties.push_back(p);};
	//void addToEnemyParties(Party* p) { enemy_parties.push_back(p); };
	void remove_party(Party* p);
	//void remove_enemy_party(Party* p);
	vector<Party*> getParties() { return parties; };
	//bool isEnemyParty(Party* p);
	//void clearEnemyParties() { enemy_parties.clear(); };
	static vector<Village*> villagesWorld;
	void set_alliance(Alliance* a) { alliance = a; };
	Alliance* get_alliance() { return alliance; };
	vector<NPC*> get_members() { return members; };
	void add_member(NPC* n) { n->setVillage(this); members.push_back(n); };
	void remove_member(NPC* n);
	void set_village_location(Vector2f loc) { location = loc; };
	Vector2f get_village_location() { return location; };
	Party* barracks;
	Party* defenders;

	void add_to_village_health(int h) { health += h; };
	void set_village_health(int h) { health = h; };
	int get_village_health() { return health; };

	void conquer(Village* v) { conquered.push_back(v); v->conquerer = this; };
	Village* get_conquerer() { return conquerer; };
	vector<Village*> get_conquered() { return conquered; };


	void static Village::init_villages();

private:
	Alliance* alliance;
	vector<NPC*> members;
	std::string status;
	Village* conquerer = nullptr;
	vector<Village*> conquered;
	std::vector<Party*> parties;
	//std::vector<Party*> enemy_parties;
	Vector2f location;
	int health;
	//vector<Village*> at_war;
};

