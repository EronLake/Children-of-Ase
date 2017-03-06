#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "common.h"
#include "Movement.h"
#include "PhysicsManager.h"
#include "CheckClass.h"



Movement::Movement(QuadTree* QT) {
	tree = QT;
	

}

Movement::~Movement() {

}

//use speed variable instead of .1

int Movement::move_up(WorldObj* obj) {
	//get list to check collision with
	if (obj->sprite.getLock())return 0;
	obj->setDirection("UP");
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float moveSpeed = npc->getSpeed();
	}
	obj->shiftY(-moveSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump","SOUND");
			LOG("failed to move up. collision.");
			obj->shiftY(moveSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_up_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("LEFT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float diagYSpeed = npc->getDiagYSpeed();
		float diagXSpeed = npc->getDiagXSpeed();
	}

	obj->shiftY(-diagYSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump", "SOUND");
			LOG("failed to move up. collision.");
			obj->shiftY(diagYSpeed*speed_magnifier);
			break;
		}
	}	
	obj->shiftX(-diagXSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump", "SOUND");
			LOG("failed to move up. collision.");
			obj->shiftX(diagXSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_up_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("RIGHT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float diagYSpeed = npc->getDiagYSpeed()*speed_magnifier;
		float diagXSpeed = npc->getDiagXSpeed()*speed_magnifier;
	}

	obj->shiftY(-diagYSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump", "SOUND");
			LOG("failed to move up. collision.");
			obj->shiftY(diagYSpeed*speed_magnifier);
			break;
		}
	}
	obj->shiftX(diagXSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			manager->createTask("Bump", "SOUND");
			LOG("failed to move up. collision.");
			obj->shiftX(-diagXSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("DOWN");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float moveSpeed = npc->getSpeed();
	}

	obj->shiftY(moveSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftY(-moveSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("LEFT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float diagYSpeed = npc->getDiagYSpeed();
		float diagXSpeed = npc->getDiagXSpeed();
	}

	obj->shiftY(diagYSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftY(-diagYSpeed*speed_magnifier);
			break;
		}
	}
	obj->shiftX(-diagXSpeed*speed_magnifier);

	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(diagXSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("RIGHT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float diagYSpeed = npc->getDiagYSpeed();
		float diagXSpeed = npc->getDiagXSpeed();
	}

	obj->shiftY(diagYSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftY(-diagYSpeed*speed_magnifier);
			break;
		}
	}
	obj->shiftX(diagXSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move down. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(-diagXSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("LEFT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float moveSpeed = npc->getSpeed();
	}
	obj->shiftX(-moveSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move left. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(moveSpeed*speed_magnifier);
			break;
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection("RIGHT");
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);

	NPC* npc;
	if (npc = CheckClass::isNPC(obj))
	{
		float moveSpeed = npc->getSpeed();
	}

	obj->shiftX(moveSpeed*speed_magnifier);
	for (int i = 0; i < objVec.size(); i++) {
		if (obj == objVec[i]) {
			break;
		}
		if (collision(objVec[i], obj)) {
			LOG("failed to move right. collision.");
			manager->createTask("Bump", "SOUND");
			obj->shiftX(-moveSpeed*speed_magnifier);
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
			if (obj == objVec[i]) {
				break;
			}
			if (objVec[i]->getInteractable()) {
				if (interaction(d, objVec[i])) {
					LOG("Player interacted with an object");
					DialogueController::startConversation(objVec[i],true);
				}
			}
		}
	}
	return 0;
}

int Movement::melee(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	Soldier* d = CheckClass::isSoldier(obj);
	if (d) {
		d->meleeAttack();
		for (int i = 0; i < objVec.size(); i++) {
			if (obj != objVec[i]) {
			LivingObj* liv = CheckClass::isLiving(objVec[i]);
			if (liv) {
				if (collision(&(d->melee), liv)) {
					std::cout << "Player hit " << liv->getName() << std::endl;
					d->melee.Hit(liv);
					std::cout << liv->getName() << "'s health is now " << liv->getHealth() << std::endl;
				}
			}
			}
		}
	}
	return 0;
}

/*int Movement::doNothing(WorldObj* obj) {
	return 0;
}*/

/*int Movement::move_toward(WorldObj* obj) {
	int result;
	NPC* npc = CheckClass::isNPC(obj);
	diagXSpeed = npc->getDiagXSpeed();
	diagYSpeed = npc->getDiagYSpeed();
	if (npc->dest.getXloc() > npc->getX()) //Destination is to the right
	{
		if (npc->dest.getYloc() > npc->getY()) { //To the right and below
			result = move_down_right(obj);
		}
		else { //To the right and above
			result = move_up_right(obj);
		}
	}  // Destination is to the left
	else {
		if (npc->dest.getYloc() > npc->getY()) { //To the left and below
			result = move_down_left(obj);
		}
		else { //To the left and above
			result = move_up_left(obj);
		}
	}
	diagXSpeed = diagSpeed;
	diagYSpeed = diagSpeed;
	return result;
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
