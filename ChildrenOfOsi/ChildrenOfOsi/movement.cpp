#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "common.h"
#include "Movement.h"


Movement::Movement(QuadTree* QT) {
	tree = QT;
}
Movement::~Movement() {

}

//use speed variable instead of .1

int Movement::move_up(WorldObj* obj) {
	//get list to check collision with
	objVec = tree->retrieve(objVec, obj);
	obj->shiftY(-0.01);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move up. collision.");
			obj->shiftY(0.01);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down(WorldObj* obj) {
	//get list to check collision with
	objVec = tree->retrieve(objVec, obj);
	obj->shiftY(0.01);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			obj->shiftY(-0.01);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_left(WorldObj* obj) {
	//get list to check collision with
	objVec = tree->retrieve(objVec, obj);
	obj->shiftX(-0.01);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move left. collision.");
			obj->shiftX(0.01);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_right(WorldObj* obj) {
	//get list to check collision with
	objVec = tree->retrieve(objVec, obj);
	obj->shiftX(0.01);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move right. collision.");
			obj->shiftX(-0.01);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}

/*void Movement::init_task_map() {
	taskMap.emplace("Move_Up", &Movement::move_up);
	taskMap.emplace("Move_Down", &Movement::move_down);
	taskMap.emplace("Move_Left", &Movement::move_left);
	taskMap.emplace("Move_Right", &Movement::move_right);
}*/

bool Movement::collision(WorldObj* recA, WorldObj* recB)
{
	bool xCollide = coordOverlap(recA->getX(), recB->getX(), recB->getX() + recB->getWidth()) || coordOverlap(recB->getX(), recA->getX(), recA->getX() + recA->getWidth());
	bool yCollide = coordOverlap(recA->getY(), recB->getY(), recB->getY() + recB->getHeight()) || coordOverlap(recB->getY(), recA->getY(), recA->getY() + recA->getHeight());
	return xCollide && yCollide;

}
