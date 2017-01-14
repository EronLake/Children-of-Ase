#include "WorldObj.h"
#include <iostream>
#include <string>

using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(float x, float y, bool col)
{
	loc.setXloc(x);
	loc.setYloc(y);
	rotation.setXloc(1);
	rotation.setYloc(1);
	collision = col;
	cout <<"X-Loc: "<< loc.getXloc() << endl;
	cout << "Y-Loc: " << loc.getYloc() << endl;
	cout << "Rotation: " << rotation.getXloc()<<" , " << rotation.getYloc()<< endl;
	cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

Vector2f WorldObj::getLoc()
{
	return loc;
}

void WorldObj::setLoc(Vector2f l)
{
	loc = l;
}

float WorldObj::getX()
{
	return loc.getXloc();
}

void WorldObj::setX(float x)
{
	loc.setXloc(x);
}

float WorldObj::getY()
{
	return loc.getYloc();
}

void WorldObj::setY(float y)
{
	loc.setYloc(y);
}

void WorldObj::shiftX(float dist)
{
	loc.shiftXloc(dist);
}

void WorldObj::shiftY(float dist)
{
	loc.shiftYloc(dist);
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

void WorldObj::setCollision(bool c)
{
	collision = c;
}

bool WorldObj::getCollision()
{
	return collision;
}

/*void WorldObj::setName(string na)
{
	name=na;
}

string WorldObj::getName()
{
	return name;
}
*/
