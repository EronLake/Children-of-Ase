#include "stdafx.h"
#include "WorldObj.h"
#include "GameWindow.h"
int WorldObj::idNum = 0;


WorldObj::WorldObj()
{
	loc.setXloc(0);
	loc.setYloc(0);
	collision = false;
	Rectangle init(loc, 1, 1);
	body.push_back(init);
	type = 0;
	ID = idNum++;
}

WorldObj::WorldObj(float x, float y, bool col)
{
	loc.setXloc(x);
	loc.setYloc(y);
	//rotation.setXloc(1);
	//rotation.setYloc(1);
	collision = col;
	Rectangle init(loc,1,1);
	body.push_back(init);
	type = 0;
	ID = idNum++;
	//cout <<"X-Loc: "<< loc.getXloc() << endl;
	//cout << "Y-Loc: " << loc.getYloc() << endl;
	//cout << "Rotation: " << rotation.getXloc()<<" , " << rotation.getYloc()<< endl;
	//cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

float WorldObj::getX()
{
	return loc.getXloc();
}

void WorldObj::setX(float x)
{
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(x+(loc.getXloc()-body[i].getX()));
	}
	loc.setXloc(x);
}

float WorldObj::getY()
{
	return loc.getYloc();
}

void WorldObj::setY(float y)
{
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(y + (loc.getYloc() - body[i].getY()));
	}
	loc.setYloc(y);
}

void WorldObj::shiftX(float dist)
{
	loc.shiftXloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(body[i].getX() + dist);
	}
}

void WorldObj::shiftY(float dist)
{
	loc.shiftYloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(body[i].getY()+dist);
	}
}

Vector2f WorldObj::getRot()
{
	return rotation;
}

float WorldObj::getRotX()
{
	return rotation.getXloc();
}

void WorldObj::setRotX(float x)
{
	rotation.setXloc(x);
}

float WorldObj::getRotY()
{
	return rotation.getYloc();
}

void WorldObj::setRotY(float y)
{
	rotation.setYloc(y);
}

void WorldObj::shiftRotX(float dist)
{
	rotation.shiftXloc(dist);
}

void WorldObj::shiftRotY(float dist)
{
	rotation.shiftYloc(dist);
}

void WorldObj::setRot(Vector2f r)
{
	rotation = r;
}

void WorldObj::setWidth(float w)
{
	width=w;
	body[0].setWidth(w);
}

void WorldObj::setHeight(float h)
{
	height=h;
	body[0].setHeight(h);
}

WorldObj::WorldObj(Vector2f p_topLeft, float p_width, float p_height) {
	loc= p_topLeft;
	width = p_width;
	height = p_height;
	Rectangle init(loc, p_width, p_height);
	body.push_back(init);
	type = 0;
}

void WorldObj::drawObj(float _x, float _y)
{
	osi::GameWindow::drawSprite(loc.getXloc()-_x, loc.getYloc()-_y, width, height, sprite);
}

void WorldObj::offsetBody(int i, float x1, float x2, float y1, float y2) {
	body[i].setX(body[i].getX()+x1);
	body[i].setY(body[i].getY() + y1);
	//cout << "body X is " << body[i].getX() << " and Y is " << body[i].getY();
	body[i].setWidth(body[i].getWidth() - (x1+x2));
	body[i].setHeight(body[i].getHeight() -(y1+y2));
	//cout << "body width is " << body[i].getWidth() << " and height is " << body[i].getHeight();

}
void WorldObj::_print() {
	std::cout << "Object Name" << getName() << std::endl;
	std::cout << "X Location" << getX() << std::endl;
	std::cout << "Y Location" << getY() << std::endl;
	std::cout << "Rotation Vector" << getX() << std::endl;
	std::cout << "Width" << getY() << std::endl;
	std::cout << "Height" << getX() << std::endl;
}

int WorldObj::getEvasionRadius()
{
	return evasionRadius;
}

void WorldObj::setEvasionRadius(std::size_t _radius)
{
	evasionRadius = _radius;
}

bool WorldObj::targetIsWithinRange(Rectangle _bound) {

	return (combatMoveDestination.getXloc() > _bound.getX()
		&& combatMoveDestination.getXloc() < _bound.getX() + _bound.getWidth()
		&& combatMoveDestination.getYloc() > _bound.getY()
		&& combatMoveDestination.getYloc() < _bound.getY() + _bound.getHeight());

}

//takes in a worldobj, returns a vector2f denoting where current obj is suppose to move to
Vector2f WorldObj::getEvadeRange(WorldObj * _enemy)
{
	//gen the rectangle bound to move
	float leftBound = _enemy->getX() - _enemy->getEvasionRadius();
	Rectangle rangeBound(Vector2f((_enemy->getX() - _enemy->getEvasionRadius()), (_enemy->getY() - _enemy->getEvasionRadius())), 2 *_enemy->getEvasionRadius(), 2 * _enemy->getEvasionRadius());
	if (targetIsWithinRange(rangeBound)) return combatMoveDestination;
	float XCoord = rand() % (int)(rangeBound.getWidth() + rangeBound.getX());
	float YCoord = rand() % (int)(rangeBound.getHeight() + rangeBound.getY());
	combatMoveDestination = Vector2f(XCoord, YCoord);
	return combatMoveDestination;
}

Vector2f WorldObj::getCombatMoveDestination()
{
	return combatMoveDestination;
}

