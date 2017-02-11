#include "stdafx.h"
#include "RenderHelper.h"


RenderHelper::RenderHelper(QuadTree * QT)
{
	tree = QT;
	cameraSize.setXloc(960);
	cameraSize.setYloc(540);
	mapSize.setXloc(10000);
	mapSize.setYloc(10000);
}

RenderHelper::~RenderHelper()
{
}

void RenderHelper::initCamera(WorldObj * player)
{
	//if player is within the four corners of the screen, camera is just the four corner of the screen
	camera = player;
	float camX = player->getX() - (mapSize.getXloc() / 2) + (player->getWidth() / 2);
	float camY = player->getY() - (mapSize.getYloc() / 2) + (player->getHeight() / 2);
	camera->setLoc(Vector2f(camX, camY));
	camera->setWidth(cameraSize.getXloc());
	camera->setHeight(cameraSize.getYloc());
	//cout << "Camera has coord " << camera->getX() << ", " << camera->getY() << " and width and height of " << camera->getWidth() << ", " << camera->getHeight() << endl;


}

// Don't need to pass in obj to draw frame, but will pass in to keep consistent style in map and pass in player to get camera coord.
int RenderHelper::draw_frame(WorldObj * obj)
{
	initCamera(obj);
	//pass in the camera bound for rendering instead of the object
	objVec = tree->retrieve(objVec, camera);
	for (int i = 0; i < objVec.size(); i++) {
		LOG("BEFORE DRAWING**");
		cout << objVec[i]->getX() - camera->getX() << endl;
		objVec[i]->WorldObj::drawObj(objVec[i]->getX() - camera->getX(), objVec[i]->getY() - camera->getY());
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



