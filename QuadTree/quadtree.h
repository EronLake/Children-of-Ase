//file: quadtree.h
#ifndef QUADTREE_H
#define QUADTREE_H
#include "common.h"
using namespace std;

class QT{
	private:
		int maxObj = 100;
		int maxLevel = 10;
		int treelv;
		Rectangle* bounds;
		vector<Rectangle*> objs;
		vector<QT*> nodes;

	public:
		QT(int p_treelv, Rectangle* p_bounds);
		~QT(){};
		void clear();
		void split();
		int getIndex(Rectangle* myrec);
		void insert(Rectangle* myrec);
		vector<Rectangle*> retrieve(vector<Rectangle*> &listOfObj, Rectangle* myrec);
}