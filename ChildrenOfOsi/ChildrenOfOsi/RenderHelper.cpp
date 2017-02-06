#include "stdafx.h"
#include "RenderHelper.h"
#include <iterator>

RenderHelper::RenderHelper()
{
	Camera = new WorldObj(0,0,true);
	Camera->setHeight(1000);
	Camera->setWidth(1000);
}


RenderHelper::~RenderHelper()
{
}

void RenderHelper::getRenderObjs(vector<WorldObj*> collidable)
{
	objVec.clear();
	for (vector<WorldObj*>::iterator i=collidable.begin(); i != collidable.end(); ++i) {
		if (Collision(Camera, *i))objVec.push_back(*i);
	}
}

bool RenderHelper::Collision(WorldObj* recA, WorldObj* recB)
{
	bool xCollide = coordOverlap(recA->getX(), recB->getX(), recB->getX() + recB->getWidth()) || coordOverlap(recB->getX(), recA->getX(), recA->getX() + recA->getWidth());
	bool yCollide = coordOverlap(recA->getY(), recB->getY(), recB->getY() + recB->getHeight()) || coordOverlap(recB->getY(), recA->getY(), recA->getY() + recA->getHeight());
	return xCollide && yCollide;

}