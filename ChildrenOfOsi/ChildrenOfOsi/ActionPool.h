#pragma once
#include "Action.h"

class ActionPool
{
public:
	ActionPool(Hero* h);
	~ActionPool();
	vector<Action> micro;
	vector<Action> macro;
	unordered_map<std::string, vector<Action*>> middleLink;
	vector<Action> getActions(Hero* h, Action macro);
	void setOwner(Hero* o) { owner = o; };
	Hero* getOwner() { return owner; };
	void updateMiddle();
private:
	Hero* owner;
	vector<Action*> addVec(vector<Action*> a, vector<Action*> b);
};

