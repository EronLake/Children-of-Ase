#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "common.h"
#include "Movement.h"
#include "PhysicsManager.h"




Movement::Movement(QuadTree* QT) {
	tree = QT;
	

}

Movement::~Movement() {

}

//use speed variable instead of .1

int Movement::move_up(WorldObj* obj) {
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	obj->shiftY(-moveSpeed);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump","SOUND");
			LOG("failed to move up. collision.");
			obj->shiftY(moveSpeed);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down(WorldObj* obj) {
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	obj->shiftY(moveSpeed);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftY(-moveSpeed);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_left(WorldObj* obj) {
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	obj->shiftX(-moveSpeed);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move left. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(moveSpeed);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_right(WorldObj* obj) {
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	obj->shiftX(moveSpeed);
	for (int i = 0; i < objVec.size(); i++) {
		if (collision(objVec[i], obj)) {
			LOG("failed to move right. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(-moveSpeed);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}

int Movement::talk(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	if (CheckClass::isPlayer(obj)) {
		Player* d = dynamic_cast<Player*>(obj);
		d->updateTalk();
		std::cout << "Talking Width "<< d->talk.getWidth()<<std::endl;
		for (int i = 0; i < objVec.size(); i++) {
			if (objVec[i]->getInteractable()) {
				if (interaction(d, objVec[i])) {
					LOG("Player interacted with an object");
					DialogueController::startConversation(objVec[i],true);
					return 1;
				}
			}
		}
	}
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
	for (int i = 0; i < (*recA).body.size(); i++) {
		for (int j = 0; j < (*recB).body.size(); j++) {
			bool xCollide = coordOverlap(recA->body[i].getX(), recB->body[j].getX(), recB->body[j].getX() + recB->body[j].getWidth()) || coordOverlap(recB->body[j].getX(), recA->body[i].getX(), recA->body[i].getX() + recA->body[i].getWidth());
			bool yCollide = coordOverlap(recA->body[i].getY(), recB->body[j].getY(), recB->body[j].getY() + recB->body[j].getHeight()) || coordOverlap(recB->body[j].getY(), recA->body[i].getY(), recA->body[i].getY() + recA->body[i].getHeight());
			if (xCollide && yCollide)return true;
		}
	}
	return false;
}

bool Movement::interaction(Player* recA, WorldObj* recB)
{
	for (int j = 0; j < (*recB).body.size(); j++) {
			bool xCollide = coordOverlap(recA->talk.getX(), recB->body[j].getX(), recB->body[j].getX() + recB->body[j].getWidth()) || coordOverlap(recB->body[j].getX(), recA->talk.getX(), recA->talk.getX() + recA->talk.getWidth());
			bool yCollide = coordOverlap(recA->talk.getY(), recB->body[j].getY(), recB->body[j].getY() + recB->body[j].getHeight()) || coordOverlap(recB->body[j].getY(), recA->talk.getY(), recA->talk.getY() + recA->talk.getHeight());
			if (xCollide && yCollide)return true;
	}
	return false;
}
