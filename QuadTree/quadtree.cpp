/* Alexander Ou
   Simple Quadtree
   
	TO USE: init quad tree with game screen. at every frame, clear tree, insert all obj we want to be considered for the collision.
	Go through each obj and retrieve list of objects it could collide with, and detect collision with a CD algo.

   */


#include "quadtree.h"
#include "common.h"

using namespace std;

QT::QT(int p_treelv, Rectangle* p_bounds) {
	treelv = p_treelv;
	bounds = p_bounds;
}


//clear quadtree
void QT::clear() {
	objs.clear();
	for(int i=0; i<nodes.size();i++) {
		if(nodes[i] != nullptr) {
			nodes[i]->clear();
			nodes[i] = nullptr;
		}
	}
}


//split node into 4 subnodes
void split(){
	int swidth = bounds->getWidth()/2;
	int slength = bounds->getLength()/2;
	int x = bounds->getX();
	int y = bounds->getY();

	nodes[0] = new QT(treelv+1, new Rectangle(x+swidth,y,swidth,slength));
	nodes[1] = new QT(treelv+1, new Rectangle(x, y, swidth, slength));
   	nodes[2] = new QT(treelv+1, new Rectangle(x, y + slength, swidth, slength));
   	nodes[3] = new QT(treelv+1, new Rectangle(x + swidth, y + slength, swidth, slength));
}

//get the index of the node where an obj can fit into
int getIndex(Rectangle* myrec) {
	//int index = -1;	//obj belongs in parent node
	double vertMdPt = bounds->getX()+bounds->getWidth()/2;
	double horiMdPt = bounds->getY()+bounds->getLength()/2;
	bool fitTop = (myrec->getY() < horiMdPt && myrec->getLength() < horiMdPt);
	bool fitBot = (myrec->getX() > horiMdPt);
		if(myrec->getX() < vertMdPt && myrec->getWidth() < vertMdPt) {		//fit in the left quadrants
			if(fitTop) {
				return 1;
			}else if(fitBot){
				return 2;
			}else if(myrec->getX() > vertMdPt) {	//fit in the right quadrants
				if(fitTop) {
					return 0;
				}else if(fitBot) {
					return 3;
				}
			}
			return -1;
		}

void insert(Rectangle* myrec) {
	if(nodes[0] != nullptr) {			//first determine which node to add obj to
		int index = getIndex(myrec);
		if(index != -1) {
			nodes[index]->insert(myrec);
				return;
		}
	}
	objs.push_back(myrec);
	if(objs.size() > maxObj && treelv < maxLevel) {	//if the # of obj in node exceeds maxObj and if we can have more trees
		if(nodes[0] == nullptr) {
			split();
		}
		for(auto it = objs.begin(); it != objs.begin();) {					//after split, add all valid obj to child node if possible, else add to parent node
			int index = getIndex(*it);
			if(index != -1) {
				nodes[index]->insert(*it);		//insert obj into child node, erase from parent list
				objs.erase(it);
			}else{
				it++;
			}
		}
	}
}

vector<Rectangle*> retrieve(vector<Rectangle*> &listOfObj, Rectangle* myrec) {
	int index = getIndex(myrec);	//get index of obj
	if(index != -1 && nodes[0] != nullptr) {
		nodes[index]->retrieve(listOfObj, myrec);
	}
	listOfObj.insert(listOfObj.end(), objs.begin(),objs.end());	//append all objects in the node to listOfObj
	return listOfObj;
}


