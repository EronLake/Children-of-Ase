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
	void setOwner(Hero* o) { owner = o; };//preConditionsNeeded also sets owner
	Hero* getOwner() { return owner; };
	vector<std::string> preConditionsNeeded(Hero* o, Hero* h);
	int exeAction();
	void setName(string n) { name = n; };
	string getName() { return name; };
	Personality* multipliers;
	void setMultipliers(int a, int k, int h, int p, int r, int e, int g);
private:
	std::string name;
	int utility;
	Hero* owner;
	Hero* hero;
};

