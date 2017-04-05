#pragma once

#include "common.h"
#include "Village.h"
#include "War.h"
#include "Party.h"

class Alliance
{
private:
	std::vector<Village*> allies;
	std::vector<NPC*> members;
	std::vector<Village*> enemies;
	static std::vector<Alliance*>Alliances;

public:
	Alliance();
	Alliance(Village* v);
	~Alliance();
	void add_to_alliance(Village* p_factionToAdd);
	void add_alliance_to_alliance(Alliance* p_allianceToAdd);
	vector<Village*> get_alligned_villages(){ return allies; };
	vector<NPC*> get_alliance_members();
	bool is_alliance_member(NPC* n);
	vector<Village*> get_enemy_villages() { return enemies; };
	void remove_from_alliance(Village* p_factionToRemove);
	static void remove_alliance(Alliance* p_allianceToRemove);
	static void update_enemies();
};

