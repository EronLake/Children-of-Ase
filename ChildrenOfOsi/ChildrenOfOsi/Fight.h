#pragma once
#include "common.h"
#include "Player.h"
#include "Party.h"
#include "Village.h"
#include "Alliance.h"
#include "War.h"

class Fight
{
public:
	Fight();
	Fight(Party* a, Party* b);
	~Fight();
	static vector<Fight*> fights_world;
	int get_radius();
	Vector2f loc;
	void add_to_attackers(Party* p);
	void add_to_defenders(Party* p);
	void update();
	void bring_out_your_dead();
private:
	vector<vector<Party*>> attackers; //attack or defense only determines ability to flee, not sides
	vector<vector<Party*>> defenders;
	vector<Party*> downed;
};

