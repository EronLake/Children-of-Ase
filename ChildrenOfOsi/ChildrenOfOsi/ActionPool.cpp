#include "stdafx.h"
#include "ActionPool.h"


ActionPool::ActionPool(Hero* h)
{
	doer = h;
	//micro.push_back({});
	//macro.push_back({});
	//middleLink["affAbove"];
	//middleLink["affBelow"];
	//middleLink["notAbove"];
	//middleLink["notBelow"];
	//middleLink["strAbove"];
	//middleLink["strBelow"];
}


ActionPool::~ActionPool()
{
}

vector<Action> ActionPool::getActions(Hero* h, Action macro)
{
	vector<Action*> points;
	vector<Action> list;
	
	vector<std::string> needs = macro.preConditionsNeeded(doer,h);
	for (int i = 0; i < needs.size(); i++) {
		auto j = middleLink.find(needs[i]);
		if (j != middleLink.end()) points=addVec(points,j->second);
	}
	for (int p= 0; p < points.size(); p++) {
		list.push_back(*points[p]);
		list.back().setReceiver(h);
		list.back().setDoer(doer);
	}
	return list;
}

vector<Action*> ActionPool::addVec(vector<Action*> a, vector<Action*> b) {
	bool copy;
	for (int i = 0; i < b.size(); i++) {
		copy = false;
		for (int j = 0; j < a.size(); j++) {
			if (a[j] == b[i])copy = true;
		}
		if (!copy) {
			a.push_back(b[i]);
		}
	}
	return a;
}

void ActionPool::updateMiddle() {
	for (int i = 0; i < macro.size(); i++) {
		for (auto it = macro[i]->req_preconds.begin(); it != macro[i]->req_preconds.end(); ++it) {
			middleLink[(*it)->get_type()];
		}
	}
	for (int i = 0; i < micro.size(); i++) {
		for (auto it = micro[i]->req_preconds.begin(); it != micro[i]->req_preconds.end(); ++it) {
			middleLink[(*it)->get_type()];
		}
	}
	for (int j = 0; j < micro.size(); j++) {
		for (auto itor = micro[j]->succ_postconds.begin(); itor != micro[j]->succ_postconds.end(); ++itor) {
			middleLink[(*itor)->get_type()].push_back(micro[j]);
		}
	}
}
