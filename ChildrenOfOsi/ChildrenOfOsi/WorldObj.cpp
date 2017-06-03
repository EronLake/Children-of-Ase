#include "stdafx.h"

#include "WorldObj.h"

#include "GameWindow.h"

int WorldObj::idNum = 0;

void WorldObj::setX(float x)
{
	//std::lock_guard<std::mutex> guard(*this->mew);
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(x-(loc.getXloc()-body[i].getX()));
	}
	loc.setXloc(x);
	effect.setX(x);
}

void WorldObj::setY(float y)
{
	//std::lock_guard<std::mutex> guard(*this->mew);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(y - (loc.getYloc() - body[i].getY()));
	}
	loc.setYloc(y);
	effect.setY(y);
}

void WorldObj::shiftX(float dist)
{
	//std::lock_guard<std::mutex> guard(*this->mew);
	loc.shiftXloc(dist);
	effect.setX(effect.getX() + dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(body[i].getX() + dist);
	}
	//std:://////cout << name<<": Body X: " << body[0].getX() << " X: "<<loc.getXloc() << std::endl;
	//std:://////cout << "X Offset" << body[0].getX()-loc.getXloc() << std::endl;
}

void WorldObj::shiftY(float dist)
{
	//std::lock_guard<std::mutex> guard(*this->mew);
	loc.shiftYloc(dist);
	effect.setY(effect.getY()+dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(body[i].getY()+dist);
	}
	//std:://////cout << name << ": Body Y: " << body[0].getY() << " Y: " << loc.getYloc() << std::endl;
	//std:://////cout << "Y Offset" << body[0].getY() - loc.getYloc() << std::endl;
}

void WorldObj::drawObj(float _x, float _y)
{
	GameWindow::drawSprite(loc.getXloc()-_x, loc.getYloc()-_y, width, height, sprite);
}

void WorldObj::offsetBody(int i, float x1, float x2, float y1, float y2) {
	//std::lock_guard<std::mutex> guard(*this->mew);
	offset_x1 += x1;
	offset_x2 += x2;
	offset_y1 += y1;
	offset_y2 += y2;
	body[i].setX(body[i].getX()+x1);
	body[i].setY(body[i].getY() + y1);
	body[i].setWidth(body[i].getWidth() - (x1+x2));
	body[i].setHeight(body[i].getHeight() -(y1+y2));

}

void WorldObj::offset_effect(int i, float x1, float x2, float y1, float y2) {
	//std::lock_guard<std::mutex> guard(*this->mew);
	//offset_x1 -= x1;
	//offset_x2 -= x2;
	//offset_y1 -= y1;
	//offset_y2 -= y2;
	effect.setX(body[i].getX() - x1);
	effect.setY(body[i].getY() - y1);
	effect.setWidth(body[i].getWidth() + (x1 + x2));
	effect.setHeight(body[i].getHeight() + (y1 + y2));

}

void WorldObj::setDirWithBase(int od, bool update)
{
	if (update)baseDir = direction;
	switch (od) {
	case WorldObj::DIRECTION_UP:
			if (baseDir == DIRECTION_DOWN) od = DIRECTION_DOWN;
			else if (baseDir == DIRECTION_LEFT) od = DIRECTION_LEFT;
			else if (baseDir == DIRECTION_RIGHT) od = DIRECTION_RIGHT;
			break;
	case WorldObj::DIRECTION_DOWN:
			if (baseDir == DIRECTION_DOWN) od = DIRECTION_UP;
			else if (baseDir == DIRECTION_LEFT) od = DIRECTION_RIGHT;
			else if (baseDir == DIRECTION_RIGHT) od = DIRECTION_LEFT;
			break;
	case WorldObj::DIRECTION_LEFT:
			if (baseDir == DIRECTION_DOWN) od = DIRECTION_RIGHT;
			else if (baseDir == DIRECTION_LEFT) od = DIRECTION_DOWN;
			else if (baseDir == DIRECTION_RIGHT) od = DIRECTION_UP;
			break;
	case WorldObj::DIRECTION_RIGHT:
			if (baseDir == DIRECTION_DOWN) od = DIRECTION_LEFT;
			else if (baseDir == DIRECTION_LEFT) od = DIRECTION_UP;
			else if (baseDir == DIRECTION_RIGHT) od = DIRECTION_DOWN;
			break;
	}
  setDirection(od);
}

void WorldObj::face(WorldObj* other) {
	//int f = WorldObj::DIRECTION_RIGHT;
	/*if (body[0].getX() > other->body[0].getX()) {
		if (body[0].getY() > other->body[0].getY()) {
			if (body[0].getX() > other->body[0].getX() + other->body[0].getWidth()) {
				f = WorldObj::DIRECTION_LEFT;
			}
			else {
				f = WorldObj::DIRECTION_UP;
			}
		}
		else {
			f = WorldObj::DIRECTION_DOWN;
		}
	}*/
	int f;
	int midX = this->body[0].getX() + (this->body[0].getWidth() / 2);
	int midY = this->body[0].getY() + (this->body[0].getHeight() / 2);

	int midX2 = other->body[0].getX() + (other->body[0].getWidth() / 2);
	int midY2 = other->body[0].getY() + (other->body[0].getHeight() / 2);

	int diffX = abs(midX - midX2);
	int diffY = abs(midY - midY2);

	if (diffX > diffY) {
		if (midX2>midX) {
			f = WorldObj::DIRECTION_RIGHT;
		} else f = WorldObj::DIRECTION_LEFT;
	}
	else {
		if (midY2>midY) {
			f = WorldObj::DIRECTION_DOWN;
		} else f = WorldObj::DIRECTION_UP;
	}

	setDirection(f);
}
/*
//takes in a worldobj, returns a vector2f denoting where current obj is suppose to move to
Vector2f WorldObj::getEvadeRange(WorldObj * _enemy)
{
	//gen the rectangle bound to move
	float leftBound = _enemy->getX() - _enemy->getEvasionRadius();
	evasionBound = new Rectangle(Vector2f((_enemy->getX() - _enemy->getEvasionRadius()), (_enemy->getY() - _enemy->getEvasionRadius())), 2 *_enemy->getEvasionRadius(), 2 * _enemy->getEvasionRadius());
	if (targetIsWithinRange(evasionBound)) {
		//////cout << "COMBAT DESTINATION FROM EVADERANGE IS " << combatMoveDestination.getXloc() << ", " << combatMoveDestination.getYloc() << endl;
		return combatMoveDestination;
	}
	float XCoord = rand() % (int)evasionBound->getWidth() + (int)evasionBound->getX();
	float YCoord = rand() % (int)evasionBound->getHeight() + (int)evasionBound->getY();
	combatMoveDestination = Vector2f(XCoord, YCoord);

	//////cout << "COMBAT DESTINATION FROM EVADERANGE IS " << combatMoveDestination.getXloc() << ", " << combatMoveDestination.getYloc() << endl;
	return combatMoveDestination;
}

Vector2f WorldObj::getStrafeLocation(WorldObj * _enemy)
{
	float XCoord;
	if (this->getX() < ((evasionBound->getX() + evasionBound->getWidth()) / 2)) {
		//XCoord = rand() % 50 + ((int)evasionBound->getX()+(int)evasionBound->getWidth() - 50);
		XCoord = rand() % (int)evasionBound->getWidth() + (int)evasionBound->getX();
	}
	else {
		XCoord = rand() % 50 + ((int)evasionBound->getX());
	}
	return Vector2f(XCoord, combatMoveDestination.getYloc());

	
}
*/

void WorldObj::_print()
{
  //std:://////cout << "Object Name" << getName() << std::endl;
  //std:://////cout << "X Location" << getX() << std::endl;
  //std:://////cout << "Y Location" << getY() << std::endl;
  //std:://////cout << "Rotation Vector" << getX() << std::endl;
  //std:://////cout << "Width" << getY() << std::endl;
  //std:://////cout << "Height" << getX() << std::endl;
}
