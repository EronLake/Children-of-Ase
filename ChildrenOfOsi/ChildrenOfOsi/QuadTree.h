#pragma once
#include "stdafx.h"
#include "common.h"
#include "WorldObj.h"

using namespace std;

class QuadTree
{
private:
	unsigned int maxObj = 10;
	unsigned int maxLevel = 5;
	unsigned int treelv;
	WorldObj* bounds;
	vector<WorldObj*> objs;
	vector<QuadTree*> nodes;

public:
	QuadTree(unsigned int p_treelv, WorldObj* p_bounds);
	~QuadTree();
	void clear();
	void split();
	vector<int> getIndexes(WorldObj* myrec);
	void Insert(WorldObj* myrec);
	vector<WorldObj*> retrieve(vector<WorldObj*> &listOfObj, WorldObj* myrec);
	vector<WorldObj*> renderRetrieve(vector<WorldObj*> &listOfObj, WorldObj* myrec);
};

