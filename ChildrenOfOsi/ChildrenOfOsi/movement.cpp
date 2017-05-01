#pragma comment(lib, "user32.lib")
#include "stdafx.h"
#include "common.h"
#include "Movement.h"
#include "PhysicsManager.h"
#include "CheckClass.h"
#include "RegionState.h"


Movement::Movement(QuadTree* QT, UniformGrid* UG, RiverObj* _rivObj) {
	tree = QT;
	rivObj = _rivObj;
	grid = UG;
	//rivObj->initialize_lines();
	set_player_clone = false;
}

Movement::~Movement() {

}

//use speed variable instead of .1

int Movement::move_up(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_UP);
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	//cout << "SIZE OF OBJVEC IS ************************ " << objVec.size() << endl;
	NPC* npc;
	if (my_type >= WorldObj::TYPE_NPC) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}
		if (!set_player_clone) {
			player_clone = *obj;
			set_player_clone = true;
		}
		obj->shiftY(-moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				//manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
			//	cout << "COLLIDED ABOVE" << endl;
				obj->shiftY(moveSpeed*speed_magnifier);
				break;
			}
			else {
				//cout << "no collision" << endl;
			}
		}
		//for up and down, use vertical line in obj body
		Line temp(Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		lineVec.clear();
		lineVec = grid->retrieve_objs_in_grid(lineVec, &temp);
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(temp.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &temp)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftY(moveSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	for (int i = 0; i < 10; i++) {
		LOG("X: " << obj->getX() << " Y: " << obj->getY());
	}
	return 0;
}
int Movement::move_up_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_LEFT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}
		Line tempHori(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		Line tempVert(Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		obj->shiftY(-diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				//manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftY(diagYSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempVert.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempVert)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftY(diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}

		obj->shiftX(-diagXSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				//manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftX(diagXSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempHori.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempHori)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftX(diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_up_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_RIGHT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed()*speed_magnifier;
			float diagXSpeed = npc->getDiagXSpeed()*speed_magnifier;
		}
		Line tempHori(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		Line tempVert(Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));

		obj->shiftY(-diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				//manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftY(diagYSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempVert.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempVert)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftY(diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
		obj->shiftX(diagXSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				//manager->createTask("Bump", "SOUND");
				LOG("failed to move up. collision.");
				obj->shiftX(-diagXSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempHori.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempHori)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftX(-diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_DOWN);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}

		obj->shiftY(moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				//cout << "COLLIDED BELOW" << endl;
				//manager->createTask("Bump", "SOUND");
				obj->shiftY(-moveSpeed*speed_magnifier);
				break;
			}
			else {
				//cout << "no collision" << endl;
			}
		}
		Line temp(Point(obj->body[0].getX()+(obj->body[0].getWidth()/2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(temp.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &temp)) {
					//manager->createTask("Bump", "SOUND");
					/*for (int j = 0; j < 10; j++) {
						cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
						cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					}*/
					LOG("failed to move up. collision.");
					obj->shiftY(-moveSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_LEFT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}
		Line tempHori(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		Line tempVert(Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		obj->shiftY(diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				//manager->createTask("Bump", "SOUND");
				obj->shiftY(-diagYSpeed*speed_magnifier);
				break;
			}			else {
				//cout << "no collision" << endl;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempVert.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempVert)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftY(-diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}

		obj->shiftX(-diagXSpeed*speed_magnifier);

		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				//manager->createTask("Bump", "SOUND");
				obj->shiftX(diagXSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempHori.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempHori)) {
					//manager->createTask("Bump", "SOUND");
					for (int j = 0; j < 10; j++) {
						//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
						cout << "COLIISION WITH LINE " << rivObj->getLines()[i]->getP1().getX() << ", " << rivObj->getLines()[i]->getP1().getY() << ", " << rivObj->getLines()[i]->getP2().getX() << ", " << rivObj->getLines()[i]->getP2().getY() << endl;
						cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

						// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					}
					LOG("failed to move up. collision.");
					obj->shiftX(diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_down_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_RIGHT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float diagYSpeed = npc->getDiagYSpeed();
			float diagXSpeed = npc->getDiagXSpeed();
		}
		Line tempHori(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		Line tempVert(Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY())), Point(obj->body[0].getX() + (obj->body[0].getWidth() / 2), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		obj->shiftY(diagYSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				//cout << "COLLIDED BELOW" << endl;
				//manager->createTask("Bump", "SOUND");
				obj->shiftY(-diagYSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempVert.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempVert)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftY(-diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
		obj->shiftX(diagXSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move down. collision.");
				//manager->createTask("Bump", "SOUND");
				obj->shiftX(-diagXSpeed*speed_magnifier);
				break;
			}
		}
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(tempHori.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &tempHori)) {
					//manager->createTask("Bump", "SOUND");
					//for (int j = 0; j < 10; j++) {
					//	//cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP1().getY() << endl;
					//	cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
					//	cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					//	// EVEN AFTER I FLIP THE LINES ACROSS THE Y AXIS, WHEN THE PLAYER MOVES DOWN, THE Y COORD IS INCREASING, SO IT"S AS IF HE IS GOING UP!!!
					//}
					LOG("failed to move up. collision.");
					obj->shiftX(-diagYSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_left(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_LEFT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}
		obj->shiftX(-moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				break;
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move left. collision.");
			//	cout << "COLLIDED LEFT" << endl;
				//manager->createTask("Bump", "SOUND");
				obj->shiftX(moveSpeed*speed_magnifier);
				break;
			}
			else {
			//	cout << "no collision" << endl;
			}
		}
		//for left and right, use horizontal line for obj body
		//obj->body[0].getBL().getXloc()
		//cout << "checking against " << rivObj->getLines().size() << " lines" << endl;
		Line temp(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(temp.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &temp)) {
					//manager->createTask("Bump", "SOUND");
					/*for (int j = 0; j < 10; j++) {
						cout << "COLIISION WITH LINE " << rivObj->getLines()[i].getP1().getX() << ", " << rivObj->getLines()[i].getP1().getY() << ", " << rivObj->getLines()[i].getP2().getX() << ", " << rivObj->getLines()[i].getP2().getY() << endl;
						cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << 25000 - obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << 25000 - obj->body[0].getBR().getYloc() << endl;

					}*/
					LOG("failed to move up. collision.");
					obj->shiftX(moveSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}
int Movement::move_right(WorldObj* obj) {
	if (obj->sprite.getLock())return 0;
	int my_type = obj->getType();
	Soldier* sold;
	if ((my_type >= WorldObj::TYPE_SOLDIER) && (sold = CheckClass::isSoldier(obj)) && (sold->get_incapacitated())) {
		return 0;
	}
	obj->setDirection(WorldObj::DIRECTION_RIGHT);
	//get list to check collision with
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	NPC* npc;
	if (my_type >= 2) {
		if (npc = CheckClass::isNPC(obj))
		{
			float moveSpeed = npc->getSpeed();
		}

		obj->shiftX(moveSpeed*speed_magnifier);
		for (int i = 0; i < objVec.size(); i++) {
			if (obj == objVec[i] || (my_type >= 2 && objVec[i]->getType() >= WorldObj::TYPE_NPC)) {
				//cout << "Skip check for"<< objVec[i]->getID() << endl;
				break;
				
			}
			if (collision(objVec[i], obj)) {
				LOG("failed to move right. collision.");
				//cout << "COLLIDED RIGHT with" << objVec[i]->getID() << endl;
				//manager->createTask("Bump", "SOUND");
				obj->shiftX(-moveSpeed*speed_magnifier);
				break;
			}
			else {
				//cout << "no collision" << endl;
			}
		}
		Line temp(Point(obj->body[0].getX(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())), Point(obj->body[0].getX() + obj->body[0].getWidth(), 25000 - (obj->body[0].getY() + obj->body[0].getHeight())));
		for (int i = 0; i < rivObj->getLines().size(); i++) {
			//if (shouldCheckLineCollision(temp.getP1(), rivObj->getLines()[i].getP1(), rivObj->getLines()[i].getP2(), 200)) {
				if (lineCollision((rivObj->getLines())[i], &temp)) {
					//manager->createTask("Bump", "SOUND");
					for (int j = 0; j < 10; j++) {
						cout << "COLIISION WITH LINE " << rivObj->getLines()[i]->getP1().getX() << ", " << rivObj->getLines()[i]->getP1().getY() << ", " << rivObj->getLines()[i]->getP2().getX() << ", " << rivObj->getLines()[i]->getP2().getY() << endl;
						cout << "my obj coord is " << obj->body[0].getBL().getXloc() << ", " << obj->body[0].getBL().getYloc() << ", " << obj->body[0].getBR().getXloc() << ", " << obj->body[0].getBR().getYloc() << endl;

					}
					LOG("failed to move up. collision.");
					obj->shiftX(-moveSpeed*speed_magnifier);
					break;
				}
			//}
		}
	}
	LOG("X: " << obj->getX() << " Y: " << obj->getY());
	return 0;
}

int Movement::talk(WorldObj* obj) {
	objVec.clear();
	objVec = tree->retrieve(objVec, obj);
	if (obj->getType() == WorldObj::TYPE_PLAYER) {
		if (CheckClass::isPlayer(obj)) {
			Player* d = dynamic_cast<Player*>(obj);
			d->updateTalk();
			//std:://////cout << "Talking Width " << d->talk.getWidth() << std::endl;
			WorldObj* ot = nullptr;
			int dist = 1000;
			for (int i = 0; i < objVec.size(); i++) {
				if (obj == objVec[i]) {
					break;
				}
				if (objVec[i]->getInteractable()) {
					if (interaction(d, objVec[i])) {
						LOG("Player interacted with an object");
						Hero* hero;
						if (hero = CheckClass::isHero(objVec[i])) {
							Planner* hero_plan = AIController::get_plan(hero->name);
							if (hero_plan->give_as_quest)   //Make sure hero is willing to give up current action
							{
								if (d == AIController::pick_quest_doer(hero_plan->get_current_action())) //Hero's top pick for doer is Player
								{
									std::cout << hero->getName() << " wants to give Shango a '" << hero_plan->get_current_action()->getName() << "' quest." << endl;
								}
								else {
									std::cout << hero->getName() << " doesn't want to give Shango their '" << hero_plan->get_current_action()->getName() << "' action." << endl;
								}
							//	continue;
							}
						}
						if (dist > Party::dist_location_to_location(objVec[i]->getLoc(), obj->getLoc())) {
							ot = objVec[i];
						}
					}
				}
			}
			RegionState::switch_music = true;
			RegionState::in_village = true;
			if (ot!=nullptr)DialogueController::startConversation(ot, true);
		}
	}
	return 0;
}

int Movement::attack(WorldObj* obj) {
	for (auto a = Containers::Attack_table.begin(); a !=Containers::Attack_table.end();++a) {
		objVec.clear();
		objVec = tree->retrieve(objVec, a->second);
		objVec.push_back(obj);
		////std::////cout << "Attack Exists" << std::endl;
		if (a->second->getPause() == 0) {
			a->second->move();
		} else {
			a->second->updatePause();
			//std::////cout << "Pause: " << a->second->getPause() << std::endl;
		}
		if (a->second->getPause() == 0) {
			//cout << "Attack compared to: " << objVec.size() << endl;
			//std::////cout << "Attack Collidable" << std::endl;
			for (int i = 0; i < objVec.size(); i++) {
				if (objVec[i]->getType() > WorldObj::TYPE_WORLDOBJ) {
					LivingObj* liv = CheckClass::isLiving(objVec[i]);
					if (liv) {
						if (collision(a->second, liv) && !a->second->beenHit(liv) && (a->second->getDuration()!=0)) {
							//std:://////cout << "Player hit " << liv->getName() << std::endl;
							if (objVec[i]->getType() > WorldObj::TYPE_LIVINGOBJ) {
								NPC* npc = CheckClass::isNPC(liv);
								if (npc) {
									Soldier* s2 = CheckClass::isSoldier(a->second->get_creator());
									bool friendly=(npc->getVillage()->get_alliance()== s2->getVillage()->get_alliance());
									manager->createTaskForAudio("PlaySound", "SOUND", "SFX/hit.wav");
									if (a->second->getDestroy())a->second->setDuration(0);
									npc->sprite.unlockAnimation();
									manager->createTaskWithObj("Hurt", "DRAW", npc);
									if (objVec[i]->getType() > WorldObj::TYPE_NPC) {
										Soldier* s = CheckClass::isSoldier(npc);
										if (s) {
											vector<Attack*> delAtk = s->getCurrentAttacks();
											for (int j = 0; j < delAtk.size(); j++) {
												delAtk[j]->setDuration(0);
											}
											if (!friendly) {
												if ((s2->getType() == WorldObj::TYPE_PLAYER) && (s->getParty()->getMode()!=Party::MODE_FLEE) && (!s->get_incapacitated())) {
													if (s->get_warning() > 0) {
														s->setCurrentEnemy(s2);
														Hero* hero = dynamic_cast<Hero*>(s);
														if ((!s->getInCombat()) && (!s2->getInCombat())) {
															if (hero) {
																if (Party::dist_location_to_location(s2->getLoc(), s2->getVillage()->get_village_location()) < 500) {
																	PlayerActExecFunctions::execute_start("Conquer", hero);
																}
																else PlayerActExecFunctions::execute_start("Fight", hero);
															}
															else Fight* fight = new Fight(s->getParty(), s2->getParty(), 0);
														}
														else if ((!s->getInCombat())) {
															if (hero) {
																if (Party::dist_location_to_location(s2->getLoc(), s2->getVillage()->get_village_location()) < 500) {
																	PlayerActExecFunctions::execute_start("Conquer", hero);
																}else PlayerActExecFunctions::execute_start("Fight", hero);
															}
															s2->getParty()->get_fight()->add_party(s->getParty(), true);
															s2->getParty()->addToCurrentEnemies(s->getParty());
															s->getParty()->addToCurrentEnemies(s2->getParty());
														}
														else if ((!s2->getInCombat())) {
															if (hero) {
																if (Party::dist_location_to_location(s2->getLoc(), s2->getVillage()->get_village_location()) < 500) {
																	PlayerActExecFunctions::execute_start("Conquer", hero);
																} else PlayerActExecFunctions::execute_start("Fight", hero);
															}
															s->getParty()->get_fight()->add_party(s2->getParty(), true);
															s2->getParty()->addToCurrentEnemies(s->getParty());
															s->getParty()->addToCurrentEnemies(s2->getParty());
														}
													}
													else s->start_warning();
												}
											}
										}
									}

									if (!friendly) {
										a->second->Hit(npc);
										manager->createTaskForAudio("PlaySound", "SOUND", "SFX/hit.wav");
                    LOG("LivingObj ::" << liv << ":: has been hit. LivingObj has " << liv->getHealth() << " health left.");

										// If target is dead, remove from village and targeting
										if (npc->getHealth() <= 0) {
											if (Soldier *sold = CheckClass::isSoldier(liv)) {
												manager->createTaskWithObj("Dead", "DRAW", sold);
												sold->defeat();
											}
										}
									} else {
										a->second->addHit(npc);
									}
								}
							} else {
								a->second->Hit(liv);
								manager->createTaskForAudio("PlaySound", "SOUND", "SFX/hit.wav");
                LOG("LivingObj ::" << liv << ":: has been hit. LivingObj has " << liv->getHealth() << " health left.");

								if (liv->getHealth() <= 0) {
									if (Soldier *sold = CheckClass::isSoldier(liv)) {
										manager->createTaskWithObj("Dead", "DRAW", sold);
										sold->defeat();
									}
								}
								if (a->second->getDestroy())a->second->setDuration(0);
								liv->sprite.unlockAnimation();
								manager->createTaskWithObj("Hurt", "DRAW", liv);
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

bool Movement::lineCollision(Line* l1, Line* l2)
{
	float denom = ((l1->getP2().getX() - l1->getP1().getX()) * (l2->getP2().getY() - l2->getP1().getY())) - ((l1->getP2().getY() - l1->getP1().getY()) * (l2->getP2().getX() - l2->getP1().getX()));
	float num1 = ((l1->getP1().getY() - l2->getP1().getY()) * (l2->getP2().getX() - l2->getP1().getX())) - ((l1->getP1().getX() - l2->getP1().getX()) * (l2->getP2().getY() - l2->getP1().getY()));
	float num2 = ((l1->getP1().getY() - l2->getP1().getY()) * (l1->getP2().getX() - l2->getP1().getX())) - ((l1->getP1().getX() - l2->getP1().getX()) * (l1->getP2().getY() - l1->getP1().getY()));

	if (denom == 0) return num1 == 0 && num2 == 0;

	float r = num1 / denom;
	float s = num2 / denom;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

//using pythagorean
bool Movement::shouldCheckLineCollision(Point target, Point dest1, Point dest2, int dist)
{
	//dist of 1,2 points
	int dist1 = sqrt((target.getX() - dest1.getX())*(target.getX() - dest1.getX()) + (target.getY() - dest1.getY())*(target.getY() - dest1.getY()));
	//dist of 1,3 points
	int dist2 = sqrt((target.getX() - dest2.getX())*(target.getX() - dest2.getX()) + (target.getY() - dest2.getY())*(target.getY() - dest2.getY()));

	return (dist1 <= dist || dist2 <= dist);
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

