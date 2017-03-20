#include "stdafx.h"
#include "QuadTree.h"


QuadTree::QuadTree(unsigned int p_treelv, WorldObj * p_bounds)
{
	treelv = p_treelv;
	bounds = p_bounds;
	for(int i=0;i<4;i++) { nodes.push_back(nullptr); }
}

QuadTree::~QuadTree()
{
	for (int i = 0; i < nodes.size(); i++) {
		delete(nodes[i]);
	}
}

void QuadTree::clear()
{
	objs.clear();
	for (decltype(nodes.size()) i = 0; i<nodes.size(); i++) {
		if (nodes[i] != nullptr) {
			nodes[i]->clear();
			nodes[i] = nullptr;
		}
	}
}

void QuadTree::split()
{
	float swidth = bounds->getWidth() / 2;
	float sheight = bounds->getHeight() / 2;
	float x = bounds->getX();
	float y = bounds->getY();

	//nodes[0] = new QuadTree(treelv + 1, new WorldObj(x + swidth, y, true));//Vector2f((x + swidth),y), swidth, sheight));
	//nodes[1] = new QuadTree(treelv + 1, new WorldObj(x, y, true));//Vector2f(x, y), swidth, sheight));
	//nodes[2] = new QuadTree(treelv + 1, new WorldObj(x, y + sheight, true));//Vector2f(x, (y + sheight)), swidth, sheight));
	//nodes[3] = new QuadTree(treelv + 1, new WorldObj(x + swidth, y + sheight, true));//Vector2f((x + swidth), (y+ sheight)), swidth, sheight));
	nodes[0] = new QuadTree(treelv + 1, new WorldObj(Vector2f((x + swidth), y), swidth, sheight));
	nodes[1] = new QuadTree(treelv + 1, new WorldObj(Vector2f(x, y), swidth, sheight));
	nodes[2] = new QuadTree(treelv + 1, new WorldObj(Vector2f(x, (y + sheight)), swidth, sheight));
	nodes[3] = new QuadTree(treelv + 1, new WorldObj(Vector2f((x + swidth), (y + sheight)), swidth, sheight));
}

vector<int> QuadTree::getIndexes(WorldObj * myrec)
{
	//int index = -1;	//obj belongs in parent node
	vector<int> indexes;

	//set up mid hori and vertical line
	double vertMdPt = bounds->getX() + (bounds->getWidth() / 2);
	double horiMdPt = bounds->getY() + (bounds->getHeight() / 2);

	//set up quadrant
	bool topQuadrant = myrec->getY() >= horiMdPt;
	bool bottomQuadrant = (myrec->getY() - myrec->getHeight()) <= horiMdPt;
	bool topAndBottomQuadrant = myrec->getY() + myrec->getHeight() + 1 >= horiMdPt && myrec->getY() + 1 <= horiMdPt;

	if (topAndBottomQuadrant) {
		topQuadrant = false;
		bottomQuadrant = false;
	}

	//check if myrec is in left or right quad
	if (myrec->getX() + myrec->getWidth() + 1 >= vertMdPt && myrec->getX() - 1 <= vertMdPt)
	{
		if (topQuadrant)
		{
			indexes.push_back(2);
			indexes.push_back(3);
		}
		else if (bottomQuadrant)
		{
			indexes.push_back(0);
			indexes.push_back(1);
		}
		else if (topAndBottomQuadrant)
		{
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);
			indexes.push_back(3);
		}
	}
	// Check if object is in just right quad
	else if (myrec->getX() + 1 >= vertMdPt)
	{
		if (topQuadrant)
		{
			indexes.push_back(3);
		}
		else if (bottomQuadrant)
		{
			indexes.push_back(0);
		}
		else if (topAndBottomQuadrant)
		{
			indexes.push_back(3);
			indexes.push_back(0);
		}
	}
	// Check if object is in just left quad
	else if (myrec->getX() - myrec->getWidth() <= vertMdPt)
	{
		if (topQuadrant)
		{
			indexes.push_back(2);
		}
		else if (bottomQuadrant)
		{
			indexes.push_back(1);
		}
		else if (topAndBottomQuadrant)
		{
			indexes.push_back(2);
			indexes.push_back(1);
		}
	}
	else {
		indexes.push_back(-1);
	}

	return indexes;
//
	//bool fitTop = (myrec->getY() < horiMdPt && (myrec->getY() + myrec->getHeight()) < horiMdPt);
	//bool fitBot = (myrec->getY() > horiMdPt);
	//if (myrec->getX() < vertMdPt && (myrec->getX() + myrec->getWidth()) < vertMdPt) {		//fit in the left quadrants
	//	if (fitTop) {
	//		return 1;
	//	}
	//	else if (fitBot) {
	//		return 2;
	//	}
	//}
	//else if (myrec->getX() > vertMdPt) {	//fit in the right quadrants
	//	if (fitTop) {
	//		return 0;
	//	}
	//	else if (fitBot) {
	//		return 3;
	//	}
	//}
	//return -1;
}


void QuadTree::Insert(WorldObj * myrec)
{
	if (nodes[0] != nullptr)
	{
		vector<int> indexes = getIndexes(myrec);
		for (int i = 0; i < indexes.size(); i++)
		{
			int index = indexes[i];
			if (index != -1)
			{
				nodes[index]->Insert(myrec);
				return;
			}
		}

	}

	objs.push_back(myrec);

	if (objs.size() > maxObj && treelv < maxLevel)
	{
		if (nodes[0] == nullptr)
		{
			//for (int i = 0; i < 100; i++) {
			//	std::cout << "THE LEVEL OF THE TREE IS " << treelv << endl;
			//}
			split();
		}


		int i = 0;
		while (i < objs.size())
		{
			WorldObj* rec = objs[i];
			vector<int> indexes = getIndexes(rec);
			for (int j = 0; j < indexes.size(); j++)
			{
				int index = indexes[j];
				if (index != -1)
				{
					nodes[index]->Insert(rec);
					objs.erase(std::remove(objs.begin(), objs.end(), rec), objs.end());
				}
				else
				{
					i++;
				}
			}
		}


		/*for (auto it = objs.begin(); it != objs.end();) {
			vector<int> indexes = getIndexes(*it);
			for (int i = 0; i < indexes.size(); i++)
			{
				int index = indexes[i];
				if (index != -1)
				{
					nodes[index]->Insert(*it);
					objs.erase(it);
				}
				else
				{
					it++;
				}
			}
		}*/
	}
}



//	if (nodes[0] != nullptr) {			//first determine which node to add obj to
//		int index = getIndexes(myrec);
//		if (index != -1) {
//			nodes[index]->Insert(myrec);
//			return;
//		}
//	}
//	objs.push_back(myrec);
//	if (objs.size() > maxObj && treelv < maxLevel) {	//if the # of obj in node exceeds maxObj and if we can have more trees
//		if (nodes[0] == nullptr) {
//			split();
//		}
//		for (auto it = objs.begin(); it != objs.end();) {					//after split, add all valid obj to child node if possible, else add to parent node
//			int index = getIndexes(*it);
//			if (index != -1) {
//				nodes[index]->Insert(*it);		//insert obj into child node, erase from parent list
//				objs.erase(it);
//			}
//			else {
//				it++;
//			}
//		}
//	}
//}


vector<WorldObj*> QuadTree::retrieve(vector<WorldObj*>& listOfObj, WorldObj * myrec)
{
	vector<int> indexes = getIndexes(myrec);
	for (int i = 0; i < indexes.size(); i++) {
		int index = indexes[i];
		if (index != -1 && nodes[0] != nullptr) {
			nodes[index]->retrieve(listOfObj, myrec);
		}
		listOfObj.insert(listOfObj.end(), objs.begin(), objs.end());
	}
	return listOfObj;
	//int index = getIndexes(myrec);	//get index of obj
	//if (index != -1 && nodes[0] != nullptr) {
	//	nodes[index]->retrieve(listOfObj, myrec);
	//}
	//listOfObj.insert(listOfObj.end(), objs.begin(), objs.end());	//append all objects in the node to listOfObj
	//																//objs.clear();
	//return listOfObj;
}

vector<WorldObj*> QuadTree::renderRetrieve(vector<WorldObj*>& listOfObj, WorldObj * myrec)
{
	vector<int> indexes = getIndexes(myrec);
	for (int i = 0; i < indexes.size(); i++) {
		int index = indexes[i];
		//if (index != -1 && nodes[0] != nullptr) {
		//	nodes[index]->retrieve(listOfObj, myrec);
		//}
		listOfObj.insert(listOfObj.end(), objs.begin(), objs.end());
	}
	return listOfObj;
}





