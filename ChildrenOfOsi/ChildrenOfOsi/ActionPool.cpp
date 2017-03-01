#include "stdafx.h"
#include "ActionPool.h"


ActionPool::ActionPool(Hero* h)
{
	owner = h;
	//micro.push_back({});
	//macro.push_back({});
	middleLink["affAbove"];
	middleLink["affBelow"];
	middleLink["notAbove"];
	middleLink["notBelow"];
	middleLink["strAbove"];
	middleLink["strBelow"];
}


ActionPool::~ActionPool()
{
}

vector<Action> ActionPool::getActions(Hero* h, Action macro)
{
	vector<Action*> points;
	vector<Action> list;
	vector<std::string> needs = macro.preConditionsNeeded(owner,h);
	for (int i = 0; i < needs.size(); i++) {
		auto j = middleLink.find(needs[i]);
		if (j != middleLink.end()) points=addVec(points,j->second);
	}
	for (int p= 0; p < points.size(); p++) {
		list.push_back(*points[p]);
		list.back().setHero(h);
		list.back().setOwner(owner);
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
	for (int i = 0; i < micro.size(); i++) {
		for (auto it = micro[i].postconds.begin(); it != micro[i].postconds.end(); ++it) {
			if (it->first.compare("aff") == 0) {
				if (it->second > 0) {
					middleLink["affAbove"].push_back(&micro[i]);
				} else middleLink["affBelow"].push_back(&micro[i]);
			} else if (it->first.compare("not") == 0) {
				if (it->second > 0) {
					middleLink["notAbove"].push_back(&micro[i]);
				}
				else middleLink["notBelow"].push_back(&micro[i]);
			} else if (it->first.compare("str") == 0) {
				if (it->second > 0) {
					middleLink["strAbove"].push_back(&micro[i]);
				}
				else middleLink["strBelow"].push_back(&micro[i]);
			}
		}
	}
}
