#pragma once
#include "Action.h"

class ActionPool
{
public:
	ActionPool();
	~ActionPool();
	vector<Action> micro;
	vector<Action> macro;
	unordered_map<std::string, vector<Action*>> middleLink;
	vector<Action> getActions(Hero* h, Action macro);
	void setOwner(Hero* h) { owner = h; };
	Hero* getOwner() { return owner; };
private:
	Hero* owner;
};

