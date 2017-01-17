#include "QuadTree.h"


QuadTree::QuadTree(unsigned int p_treelv, Rectangle * p_bounds)
{
	treelv = p_treelv;
	bounds = p_bounds;
	for(int i=0;i<4;i++) { nodes.push_back(nullptr); }
}

QuadTree::~QuadTree()
{
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

	nodes[0] = new QuadTree(treelv + 1, new Rectangle(Vector2f((x + swidth),y), swidth, sheight));
	nodes[1] = new QuadTree(treelv + 1, new Rectangle(Vector2f(x, y), swidth, sheight));
	nodes[2] = new QuadTree(treelv + 1, new Rectangle(Vector2f(x, (y + sheight)), swidth, sheight));
	nodes[3] = new QuadTree(treelv + 1, new Rectangle(Vector2f((x + swidth), (y+ sheight)), swidth, sheight));
}

int QuadTree::getIndex(Rectangle * myrec)
{
	//int index = -1;	//obj belongs in parent node
	double vertMdPt = bounds->getX() + (bounds->getWidth() / 2);
	double horiMdPt = bounds->getY() + (bounds->getHeight() / 2);
	bool fitTop = (myrec->getY() < horiMdPt && (myrec->getY() + myrec->getHeight()) < horiMdPt);
	bool fitBot = (myrec->getY() > horiMdPt);
	if (myrec->getX() < vertMdPt && (myrec->getX() + myrec->getWidth()) < vertMdPt) {		//fit in the left quadrants
		if (fitTop) {
			return 1;
		}
		else if (fitBot) {
			return 2;
		}
	}
	else if (myrec->getX() > vertMdPt) {	//fit in the right quadrants
		if (fitTop) {
			return 0;
		}
		else if (fitBot) {
			return 3;
		}
	}
	return -1;
}

void QuadTree::insert(Rectangle * myrec)
{
	if (nodes[0] != nullptr) {			//first determine which node to add obj to
		int index = getIndex(myrec);
		if (index != -1) {
			nodes[index]->insert(myrec);
			return;
		}
	}
	objs.push_back(myrec);
	if (objs.size() > maxObj && treelv < maxLevel) {	//if the # of obj in node exceeds maxObj and if we can have more trees
		if (nodes[0] == nullptr) {
			split();
		}
		for (auto it = objs.begin(); it != objs.begin();) {					//after split, add all valid obj to child node if possible, else add to parent node
			int index = getIndex(*it);
			if (index != -1) {
				nodes[index]->insert(*it);		//insert obj into child node, erase from parent list
				objs.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

vector<Rectangle*> QuadTree::retrieve(vector<Rectangle*>& listOfObj, Rectangle * myrec)
{
	int index = getIndex(myrec);	//get index of obj
	if (index != -1 && nodes[0] != nullptr) {
		nodes[index]->retrieve(listOfObj, myrec);
	}
	listOfObj.insert(listOfObj.end(), objs.begin(), objs.end());	//append all objects in the node to listOfObj
	return listOfObj;
}



