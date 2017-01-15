#pragma once
#include "common.h"
#include "Rectangle.h"

using namespace std;

class Rectangle;

class QuadTree
{
private:
	unsigned int maxObj = 100;
	unsigned int maxLevel = 10;
	unsigned int treelv;
	Rectangle* bounds;
	vector<Rectangle*> objs;
	vector<QuadTree*> nodes;

public:
	QuadTree(unsigned int p_treelv, Rectangle* p_bounds);
	~QuadTree();
	void clear();
	void split();
	int getIndex(Rectangle* myrec);
	void insert(Rectangle* myrec);
	vector<Rectangle*> retrieve(vector<Rectangle*> &listOfObj, Rectangle* myrec);
};

