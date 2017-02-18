#include "stdafx.h"
#include "RenderHelper.h"


RenderHelper::RenderHelper(QuadTree * QT)
{
	tree = QT;
	camera = new WorldObj(0, 0, false);
	cameraSize.setXloc(960);
	cameraSize.setYloc(540);
	mapSize.setXloc(10000);
	mapSize.setYloc(10000);
	convoGui = new DialogueGui();
	convoGui->loadTexture();
	convoGui->setSprite();
}

RenderHelper::~RenderHelper()
{
}

void RenderHelper::initCamera(WorldObj * player)
{
	//if player is within the four corners of the screen, camera is just the four corner of the screen
	float camX = player->getX() - (cameraSize.getXloc() / 2) + (player->getWidth() / 2);
	float camY = player->getY() - (cameraSize.getYloc() / 2) + (player->getHeight() / 2);
	camera->setLoc(Vector2f(camX, camY));
	camera->setWidth(cameraSize.getXloc());
	camera->setHeight(cameraSize.getYloc());
	cout << "Camera has coord " << camera->getX() << ", " << camera->getY() << " and width and height of " << camera->getWidth() << ", " << camera->getHeight() << endl;


}

// Don't need to pass in obj to draw frame, but will pass in to keep consistent style in map and pass in player to get camera coord.
int RenderHelper::draw_frame(WorldObj * obj)
{
	initCamera(obj);
	//pass in the camera bound for rendering instead of the object
	objVec.clear();
	objVec = tree->retrieve(objVec, camera);
	obj->WorldObj::drawObj(camera->getX(), camera->getY());
	obj->WorldObj::animateObj();
	/*for (int i = 0; i < obj->body.size(); i++) {
		osi::GameWindow::drawSprite(obj->body[i].getX()-camera->getX(), obj->body[i].getY()-camera->getY(), obj->body[i].getWidth(), obj->body[i].getHeight(), obj->getSprite());
	}*/
	for (int i = 0; i < objVec.size(); i++) {
		LOG("BEFORE DRAWING**");
		//cout << objVec[i]->getX() - camera->getX() << endl;
		//LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
		objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
		objVec[i]->WorldObj::animateObj();
	}
	convoGui->drawGui();
	osi::GameWindow::refresh();
	return 0;
}

int RenderHelper::sprite_up(WorldObj * obj)
{
	obj->sprite.setTexture(obj->sprite.up);
	return 0;
}

int RenderHelper::sprite_down(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.down);
	return 0;
}

int RenderHelper::sprite_left(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.left);
	return 0;
}

int RenderHelper::sprite_right(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.right);
	return 0;
}

int RenderHelper::sprite_update(WorldObj * obj)
{
	return 0;
}



