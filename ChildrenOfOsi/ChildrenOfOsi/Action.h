#pragma once
#include "common.h"
#include "Player.h"

class Action
{
public:
	Action();
	~Action();
	unordered_map<std::string, int> preconds;
	unordered_map<std::string, int> postconds;
	void setUtility(int u) { utility = u; };
	int getUtility() { return utility; };
	void setHero(Hero* h) { hero = h; };
	Hero* getHero() { return hero; };
private:
	int utility;
	Hero* hero;
};

