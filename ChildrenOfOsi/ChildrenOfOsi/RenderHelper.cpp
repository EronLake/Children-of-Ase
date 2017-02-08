#include "stdafx.h"
#include "RenderHelper.h"


RenderHelper::RenderHelper(QuadTree * QT)
{
	tree = QT;
}

RenderHelper::~RenderHelper()
{
}

void RenderHelper::initCamera(WorldObj * player)
{
	//apply the bounding box on the player to make the camera
	

}

// Don't need to pass in obj to draw frame, but will pass in to keep consistent style in map and pass in player to get camera coord.
int RenderHelper::draw_frame(WorldObj * obj)
{
	initCamera(obj);
	//pass in the camera bound for rendering instead of the object
	objVec = tree->retrieve(objVec, obj);
	for (int i = 0; i < objVec.size(); i++) {
		objVec[i]->WorldObj::drawObj();
	}
	osi::GameWindow::refresh();
	return 0;
}

int RenderHelper::sprite_change(WorldObj * obj)
{
	return 0;
}

int RenderHelper::sprite_update(WorldObj * obj)
{
	return 0;
}



