#pragma once
#include "common.h"
#include "Player.h"
#include "Party.h"
#include "Village.h"
#include "Alliance.h"
#include "War.h"
#include "PlayerActExecFunctions.h"

class Fight
{
public:
	Fight();
	Fight(Party* a, Party* b, int tp);
	~Fight();
	int get_radius();
	void update_radius();
	void add_party(Party* p, bool atk);
	void add_to_attackers(Party* p);
	void add_to_defenders(Party* p);
	void update_fight();
	bool check_for_winner();
	bool is_over() { return over; };
	void not_over() { over=false; };
	static vector<Fight*> fights_world;
	static void update_all_fights();
	static void bring_out_your_dead();
	void end_combat();
	void find_targets();
	void help_find_targets(unordered_map<Alliance*,vector<Party*>> m);
	void set_loc(Vector2f v) { loc = v; };
	Vector2f get_loc() { return loc; };
	void check_should_flee(Party* p);
	int get_type() { return type; };
	void set_plyr_win(bool b) { player_win = b; };

	static constexpr int TYPE_FIGHT = 0;
	static constexpr int TYPE_DUEL = 1;
	static constexpr int TYPE_SPAR = 2;
	static constexpr int TYPE_TRAIN = 3;

private:
	Vector2f loc;
	vector<vector<Party*>> attackers; //attack or defense only determines ability to flee, not sides
	vector<vector<Party*>> defenders;
	vector<Party*> downed;
	bool over;
	int rad;
	int sides;
	int type;
	int num_of_fighters;
	bool player_win;
};

