#pragma once
#include "Action.h"

class ActionPool
{
public:
	ActionPool(Hero* h);
	~ActionPool();
	vector<Action*> micro;
	vector<Action*> macro;
	vector<Action*> end_states;
	unordered_map<std::string, vector<Action*>> actions_by_post;
	vector<Action*> getActions(Hero* h, Action* macro);
	void setDoer(Hero* o) { doer = o; };
	Hero* getDoer() { return doer; };
	void updateMiddle();
private:
	Hero* doer;
	vector<Action*> addVec(vector<Action*> a, vector<Action*> b);
};

