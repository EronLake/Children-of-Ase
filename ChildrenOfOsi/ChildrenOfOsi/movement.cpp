#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "common.h"
#include "Movement.h"
#include "PhysicsManager.h"
#include "CheckClass.h"



Movement::Movement(QuadTree* QT) {
	tree = QT;
	rivObj = new RiverObj();
	

}

Movement::~Movement() {

}

//use speed variable instead of .1

int Movement::move_up(WorldObj* obj) {
	//get list to check collision with
	if (obj->sprite.getLock())return 0;
	obj->setDirection(8);
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}
		obj->shiftY(-moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftY(moveSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			if (lineCollision((rivObj->getLines())[i], (Line(Point(obj->getX(), obj->getY() + 50), Point(obj->getX() + obj->getWidth(), obj->getY() + 50))))) {
				manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftY(moveSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_up_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(4);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}

		obj->shiftY(-diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
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
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftX(diagXSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_up_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(6);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed()*speed_magnifier;
			float diagXSpeed = npc->getDiagXSpeed()*speed_magnifier;
		}

		obj->shiftY(-diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
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
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftX(-diagXSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(2);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}

		obj->shiftY(moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				manager->createTask("Bump", "SOUND");
				obj->shiftY(-moveSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(4);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}

		obj->shiftY(diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
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
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				manager->createTask("Bump", "SOUND");
				obj->shiftX(diagXSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(6);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}

		obj->shiftY(diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
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
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				manager->createTask("Bump", "SOUND");
				obj->shiftX(-diagXSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(4);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}
		obj->shiftX(-moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move left. collision.");
				manager->createTask("Bump", "SOUND");
				obj->shiftX(moveSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	obj->setDirection(6);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	int my_type = obj->getType();
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}

		obj->shiftX(moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= 2)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move right. collision.");
				manager->createTask("Bump", "SOUND");
				obj->shiftX(-moveSpeed*speed_magnifier);
				break;
			}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}

int Movement::talk(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	if (obj->getType() == 6) {
		if (CheckClass::isPlayer(obj)) {
			Player* d = dynamic_cast<Player*>(obj);
			d->updateTalk();
			std::cout << "Talking Width " << d->talk.getWidth() << std::endl;
			for (int i = 0; i < objVec.size(); i++) {
				if (obj == objVec[i]) {
					break;
				}
				if (objVec[i]->getInteractable()) {
					if (interaction(d, objVec[i])) {
						LOG("Player interacted with an object");
						DialogueController::startConversation(objVec[i], true);
					}
				}
			}
		}
	}
	return 0;
}

int Movement::melee(WorldObj* obj) {
	if (obj->getType() >= 3) {
		Soldier* d = CheckClass::isSoldier(obj);
		if (d) {
			//d->meleeAttack();
			//std::cout << "Attack Added" << std::endl;
		}
	}
	return 0;
}

int Movement::specialAttack(WorldObj* obj) {
	if (obj->getType() >= 3) {
		Soldier* a = CheckClass::isSoldier(obj);
		if (a) {
			//a->newAttack(a->triedAttack(), Containers::Attack_table[a->getAtKey()]);
			std::cout << "Attack Added" << std::endl;
		}
	}
	return 0;
}

int Movement::attack(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	objVec.push_back(obj);
	for (auto a = Containers::Attack_table.begin(); a !=Containers::Attack_table.end();++a) {
		//std::cout << "Attack Exists" << std::endl;
		if (a->second->getPause() == 0) {
			a->second->move();
		} else {
			a->second->updatePause();
			std::cout << "Pause: " << a->second->getPause() << std::endl;
		}
		if (a->second->getPause() == 0) {
			std::cout << "Attack Collidable" << std::endl;
			for (int i = 0; i < objVec.size(); i++) {
				if (objVec[i]->getType() > 1) {
					LivingObj* liv = CheckClass::isLiving(objVec[i]);
					if (liv) {
						if (collision(a->second, liv) && !a->second->beenHit(liv) && (a->second->getDuration()!=0)) {
							std::cout << "Player hit " << liv->getName() << std::endl;
							a->second->Hit(liv);
							if (a->second->getDestroy())a->second->setDuration(0);
							liv->sprite.unlockAnimation();
							manager->createTaskWithObj("Hurt", "DRAW", liv);
							std::cout << liv->getName() << "'s health is now " << liv->getHealth() << std::endl;
							if (objVec[i]->getType() > 2) {
								Soldier* s = CheckClass::isSoldier(liv);
								if (s) {
									vector<Attack*> delAtk= s->getCurrentAttacks();
									for (int j = 0; j < delAtk.size();j++) {
										delAtk[j]->setDuration(0);
									}
								}
							}
						}
					}
				}
			}
			if (a->second->updateDuration()==false) {
				if (a->second->getKeep()==false) {
					manager->createTaskWithParams("Del_Attack", "MODIFY_POOL", a->first,0,0,true);
				}
				else {
					a->second->setPause(-1);
				}
			}
		}
	}
	return 0;
}

int Movement::meleeSwing(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	if (obj->getType() >= 3) {
		Soldier* d = CheckClass::isSoldier(obj);
		if (d) {
			//d->meleeAttack();
			for (int i = 0; i < objVec.size(); i++) {
				if (obj != objVec[i]) {
					if (objVec[i]->getType() >= 1) {
						LivingObj* liv = CheckClass::isLiving(objVec[i]);
						if (liv) {
							if (collision(d->melee, liv)) {
								std::cout << "Player hit " << liv->getName() << std::endl;
								d->melee->Hit(liv);
								std::cout << liv->getName() << "'s health is now " << liv->getHealth() << std::endl;
							}
						}
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

bool Movement::lineCollision(Line l1, Line l2)
{
	float denom = ((l1.getP2().getX() - l1.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY())) - ((l1.getP2().getY() - l1.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX()));
	float num1 = ((l1.getP1().getY() - l2.getP1().getY()) * (l2.getP2().getX() - l2.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l2.getP2().getY() - l2.getP1().getY()));
	float num2 = ((l1.getP1().getY() - l2.getP1().getY()) * (l1.getP2().getX() - l1.getP1().getX())) - ((l1.getP1().getX() - l2.getP1().getX()) * (l1.getP2().getY() - l1.getP1().getY()));

	if (denom == 0) return num1 == 0 && num2 == 0;

	float r = num1 / denom;
	float s = num2 / denom;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
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

